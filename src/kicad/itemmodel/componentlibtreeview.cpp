#include "componentlibtreeview.h"

ComponentLibTreeView::ComponentLibTreeView(Lib *lib, QWidget *parent) :
    QTreeView(parent)
{
    if (lib)
        _model = new ComponentLibItemModel(lib);
    else
        _model = new ComponentLibItemModel(new Lib());

    _sortProxy = new QSortFilterProxyModel();
    _sortProxy->setSourceModel(_model);
    setModel(_sortProxy);

    setSortingEnabled(true);
}

Lib *ComponentLibTreeView::lib() const
{
    return _model->lib();
}

void ComponentLibTreeView::setLib(Lib *lib)
{
    _model->setLib(lib);
}

void ComponentLibTreeView::addComponent(Component *component)
{
    _model->addComponent(component);
}

QList<Component *> ComponentLibTreeView::components() const
{
    return _model->components();
}

void ComponentLibTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTreeView::mouseDoubleClickEvent(event);

    if (!event->buttons().testFlag(Qt::LeftButton))
        return;

    const QPersistentModelIndex index = indexAt(event->pos());
    if (!index.isValid())
        return;

    const QModelIndex &indexComponent = _sortProxy->mapToSource(index);
    emit openedComponent(_model->component(indexComponent));
}