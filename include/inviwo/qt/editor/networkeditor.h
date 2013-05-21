#ifndef IVW_NETWORKEDITOR_H
#define IVW_NETWORKEDITOR_H

#include <inviwo/qt/editor/inviwoqteditordefine.h>
#include <QGraphicsScene>
#include <QTimer>

#include <inviwo/core/network/processornetworkevaluator.h>
#include <inviwo/core/processors/processorfactory.h>
#include <inviwo/core/ports/inport.h>
#include <inviwo/core/ports/outport.h>
#include <inviwo/core/util/singleton.h>

#include "processorgraphicsitem.h"
#include "connectiongraphicsitem.h"
#include "linkgraphicsitem.h"
#include "linkdialog.h"

namespace inviwo {

/**
 * The NetworkEditor supports interactive editing of a ProcessorNetwork. Processors can be added
 * and removed, and their ports can be connected, while their properties can be linked.
 * - interactive editing, but if necessary use access fucntions
 * - graphical representation automatically managed
 * - inspector networks
 */
class IVW_QTEDITOR_API NetworkEditor : public QGraphicsScene,
                                       public Singleton<NetworkEditor>  {

    Q_OBJECT
public:
    NetworkEditor(QObject* parent=0);

    /**
     * \brief This method adds a processor to the network.
     * - modified called by processornetwork
     * - models and views are added independently (e.g., addProcessor vs. addProcessorRepresentation)
     *
     * Before the processor is added to the network, its identifier is analyzed and
     * if necessary changed, such that the processor names within each network are unique.
     * 
     * @param Processor* processor The processor to be added
     * @param pos Position in the network editor, wher ethe graphical representation should be located
     * @param visible Shall the graphical representation be visible
     */
    void addProcessor(Processor* processor, QPointF pos, bool showProcessor=true, bool showProcessorWidget=true);
    void removeProcessor(Processor* processor);

    void addConnection(Outport* outport, Inport* inport);
    void removeConnection(Outport* outport, Inport* inport);

    void addLink(Processor* processor1, Processor* processor2);
    void removeLink(Processor* processor1, Processor* processor2);

    void clearNetwork();
    bool saveNetwork(std::string fileName);
    bool loadNetwork(std::string fileName);

    const ProcessorNetwork* getProcessorNetwork() const { return processorNetwork_; }
    ProcessorNetworkEvaluator* getProcessorNetworkEvaluator() const { return processorNetworkEvaluator_; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* e);

    void keyPressEvent(QKeyEvent* keyEvent);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* e);

    void dragEnterEvent(QGraphicsSceneDragDropEvent* de);
    void dragMoveEvent(QGraphicsSceneDragDropEvent* de);
    void dropEvent(QGraphicsSceneDragDropEvent* de);

private:
    friend class ProcessorGraphicsItem;
    friend class ConnectionGraphicsItem;

    std::vector<ProcessorGraphicsItem*> processorGraphicsItems_;
    std::vector<ConnectionGraphicsItem*> connectionGraphicsItems_;
    std::vector<LinkConnectionGraphicsItem*> linkGraphicsItems_;

    ProcessorNetwork* processorNetwork_;
    ProcessorNetworkEvaluator* processorNetworkEvaluator_;

    CurveGraphicsItem* connectionCurve_;
    LinkGraphicsItem* linkCurve_;

    // these members are used to save the start state for click-move events
    ProcessorGraphicsItem* startProcessor_;
    ProcessorGraphicsItem* endProcessor_;
    Port* startPort_;
    Port* endPort_;
    Port* inspectedPort_; // the port which is currently inspected by hovering over it

    bool gridSnapping_;
    static const int GRID_SPACING;
    QTimer hoverTimer_;

    void addProcessorRepresentations(Processor* processor, QPointF pos, bool showProcessor=true, bool showProcessorWidget=true);
    void removeProcessorRepresentations(Processor* processor);
    void addProcessorGraphicsItem(Processor* processor, QPointF pos, bool visible=true);
    void removeProcessorGraphicsItem(Processor* processor);
    void addPropertyWidgets(Processor* processor, bool visible=true);
    void removePropertyWidgets(Processor* processor);
    void addProcessorWidget(Processor* processor, bool visible=true);

    void removeConnection(ConnectionGraphicsItem* connectionGraphicsItem);
    void addConnectionGraphicsItem(Outport* outport, Inport* inport);
    void removeConnectionGraphicsItem(ConnectionGraphicsItem* connectionGraphicsItem);

    void removeLink(LinkConnectionGraphicsItem* linkGraphicsItem);
    void addLinkGraphicsItem(Processor* processor1, Processor* processor2);
    void removeLinkGraphicsItem(LinkConnectionGraphicsItem* linkGraphicsItem);

    void showLinkDialog(LinkConnectionGraphicsItem* linkConnectionGraphicsItem);

    ProcessorGraphicsItem* getProcessorGraphicsItem(std::string identifier) const;
    ConnectionGraphicsItem* getConnectionGraphicsItem(Outport* outport, Inport* inport) const;
    LinkConnectionGraphicsItem* getLinkGraphicsItem(Processor* processor1, Processor* processor2) const;

    ProcessorGraphicsItem* getProcessorGraphicsItemAt(const QPointF pos) const;
    ConnectionGraphicsItem* getConnectionGraphicsItemAt(const QPointF pos) const;
    LinkConnectionGraphicsItem* getLinkGraphicsItemAt(const QPointF pos) const;

    void addInspectorNetwork(Port* port, ivec2 pos, std::string fileName);
    void removeInspectorNetwork(Port* port);
    void addPortInspector(Port* port, QPointF pos);

    QPointF snapToGrid(QPointF pos);
    void drawBackground(QPainter* painter, const QRectF& rect);
    std::string obtainUniqueProcessorID(Processor* processor) const;

public slots:
    void hoverPortTimeOut();
};

} // namespace

#endif // IVW_NETWORKEDITOR_H