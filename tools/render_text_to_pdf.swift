import Foundation
import CoreText
import AppKit

func usage() -> Never {
    fputs("Usage: swift render_text_to_pdf.swift <input.txt> <output.pdf>\n", stderr)
    exit(1)
}

func makeFont(size: CGFloat) -> CTFont {
    let candidates = [
        "AppleSDGothicNeo-Regular",
        "Apple SD Gothic Neo",
        "NanumGothic",
        "Helvetica",
    ]

    for name in candidates {
        if let font = NSFont(name: name, size: size) {
            return font as CTFont
        }
    }

    return CTFontCreateWithName("Helvetica" as CFString, size, nil)
}

guard CommandLine.arguments.count == 3 else {
    usage()
}

let inputURL = URL(fileURLWithPath: CommandLine.arguments[1])
let outputURL = URL(fileURLWithPath: CommandLine.arguments[2])

let text = try String(contentsOf: inputURL, encoding: .utf8)

let paragraphStyle = NSMutableParagraphStyle()
paragraphStyle.lineBreakMode = .byWordWrapping
paragraphStyle.lineSpacing = 3
paragraphStyle.paragraphSpacing = 10

let attributes: [NSAttributedString.Key: Any] = [
    .font: makeFont(size: 12),
    .foregroundColor: NSColor.black,
    .paragraphStyle: paragraphStyle,
]

let attributedText = NSAttributedString(string: text, attributes: attributes)
let framesetter = CTFramesetterCreateWithAttributedString(attributedText as CFAttributedString)

let outputDir = outputURL.deletingLastPathComponent()
try FileManager.default.createDirectory(at: outputDir, withIntermediateDirectories: true)

var mediaBox = CGRect(x: 0, y: 0, width: 595, height: 842)
guard
    let consumer = CGDataConsumer(url: outputURL as CFURL),
    let context = CGContext(consumer: consumer, mediaBox: &mediaBox, nil)
else {
    fputs("Failed to create PDF context for \(outputURL.path)\n", stderr)
    exit(1)
}

let contentRect = mediaBox.insetBy(dx: 50, dy: 50)
var currentLocation = 0

while currentLocation < attributedText.length {
    context.beginPDFPage(nil)

    let path = CGMutablePath()
    path.addRect(contentRect)

    let frame = CTFramesetterCreateFrame(
        framesetter,
        CFRange(location: currentLocation, length: 0),
        path,
        nil
    )

    CTFrameDraw(frame, context)

    let visibleRange = CTFrameGetVisibleStringRange(frame)
    context.endPDFPage()

    if visibleRange.length == 0 {
        break
    }

    currentLocation += visibleRange.length
}

context.closePDF()
print("Created \(outputURL.path)")
