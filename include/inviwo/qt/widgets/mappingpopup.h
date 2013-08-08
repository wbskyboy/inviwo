#ifndef IVW_MAPPINGPOPUP_H
#define IVW_MAPPINGPOPUP_H


#include <inviwo/core/properties/eventproperty.h>
#include <inviwo/qt/widgets/eventconverterqt.h>
#include <inviwo/qt/editor/eventpropertymanager.h>
#include <inviwo/qt/editor/mappingwidget.h>
#include <inviwo/qt/widgets/inviwoapplicationqt.h>
#include <inviwo/qt/widgets/inviwoqtwidgetsdefine.h>

#include <QWidget>
#include <QMouseEvent>

namespace inviwo {

class MappingPopup : public QWidget {
    Q_OBJECT;

public:
    MappingPopup(EventProperty* eventProperty, EventPropertyManager* parentManager);

//protected:
	void keyReleaseEvent(QKeyEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mousePressEvent( QMouseEvent * event );

private:
	EventProperty* eventProperty_;
	EventPropertyManager* parentManager_;
};

} // namespace

#endif // IVW_MAPPINGPOPUP_H