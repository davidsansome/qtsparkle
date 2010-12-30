#include "appcast.h"
#include "compareversions.h"

#include <QXmlStreamReader>
#include <QtDebug>

namespace qtsparkle {

struct AppCast::Private {
  struct Item {
    QString version_;
    QString download_url_;
    QString release_notes_url_;

    bool operator <(const Item& other) const {
      return CompareVersions(version_, other.version_);
    }
  };
  typedef QList<Item> ItemList;

  static Item LoadItem(QXmlStreamReader* reader) {
    Item ret;

    while (!reader->atEnd()) {
      reader->readNext();

      if (reader->tokenType() == QXmlStreamReader::EndElement)
        break;

      if (reader->tokenType() == QXmlStreamReader::StartElement) {
        if (reader->name() == "releaseNotesLink" &&
            reader->namespaceUri() == Private::kNamespace) {
          ret.release_notes_url_ = reader->readElementText().trimmed();
        } else if (reader->name() == "enclosure") {
          ret.download_url_ = reader->attributes().value("url").toString();
          ret.version_ = reader->attributes().value(Private::kNamespace, "version").toString();
        } else {
          reader->skipCurrentElement();
        }
      }
    }
    return ret;
  }

  Item latest_;
  QString error_reason_;

  static const char* kNamespace;
};

const char* AppCast::Private::kNamespace = "http://www.andymatuschak.org/xml-namespaces/sparkle";


AppCast::AppCast()
  : d(new Private)
{
}

AppCast::~AppCast() {
}

QString AppCast::version() const { return d->latest_.version_; }
QString AppCast::download_url() const { return d->latest_.download_url_; }
QString AppCast::release_notes_url() const { return d->latest_.release_notes_url_; }
QString AppCast::error_reason() const { return d->error_reason_; }

bool AppCast::Load(QIODevice* dev) {
  QXmlStreamReader reader(dev);

  d->latest_ = Private::Item();
  while (!reader.atEnd()) {
    reader.readNext();

    if (reader.tokenType() == QXmlStreamReader::StartElement &&
        reader.name() == "item") {
      Private::Item item = d->LoadItem(&reader);
      if (d->latest_ < item)
        d->latest_ = item;
    }
  }

  d->error_reason_ = reader.errorString();
  return !reader.hasError();
}

} // namespace qtsparkle
