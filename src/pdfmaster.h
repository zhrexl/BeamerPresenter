#ifndef PDFMASTER_H
#define PDFMASTER_H

#include <poppler/qt5/poppler-qt5.h>
#include <poppler/qt5/poppler-version.h>
#include <QFileInfo>
#include <QInputDialog>
#include "src/slidescene.h"
#include "src/slideview.h"
#include "src/preferences.h"
#include "src/drawing/pathcontainer.h"
#include "src/rendering/pixcache.h"

/// Full document including PDF and paths / annotations added by user.
/// This should also manage drawings and multimedia content of the PDF.
class PdfMaster : public QObject
{
    Q_OBJECT

private:
    /// Poppler document representing the PDF
    Poppler::Document* document = nullptr;

    /// Path to the PDF document, used for reloading
    QString pdfpath;

    /// Last time the PDF was edited. This is compared when trying to reload
    /// the file.
    QDateTime lastModified;

    /// Map of pixmap cache maps for storing cached slides.
    /// keys are int(1000*resolution).
    QMap<int, PixCache*> pixcaches;

    /// Map page numbers to containers of paths.
    /// Paths can be drawn per slide label by creating references to the main
    /// path list from other slide numbers.
    QMap<int, PathContainer*> paths;

    // TODO: multimedia


public:
    /// Create a new PdfMaster from a given file name.
    explicit PdfMaster(const QString &filename);
    ~PdfMaster();

    /// Load or reload the file. Return true if the file was updated and false
    /// otherwise.
    bool loadDocument();

    /// Get path to PDF file.
    const QString &getFilename() const {return pdfpath;}

    /// Get size of page in points (floating point precision).
    const QSizeF getPageSize(const int page_number) const;

    /// Get Poppler::Document.
    const Poppler::Document * getDocument() const {return document;}

    /// Get page from document. Does not check whether page exists.
    const Poppler::Page * getPage(const int page) const {return document->page(page);}

public slots:
    /// Paths have changed on SlideView sender. Update paths and send out a
    /// signal to all SlideScenes.
    void updatePaths(const SlideView *sender);

signals:
    /// Notify all associated SlidesScenes that paths have changed.
    void pathsUpdated();
};

#endif // PDFMASTER_H
