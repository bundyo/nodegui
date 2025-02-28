import addon from '../utils/addon';
import { NodeWidget } from './QWidget';
import { BaseWidgetEvents } from '../core/EventWidget';
import { NativeElement } from '../core/Component';
import { QAbstractScrollArea } from './QAbstractScrollArea';

export const QScrollAreaEvents = Object.freeze({
    ...BaseWidgetEvents,
});
export class QScrollArea extends QAbstractScrollArea {
    native: NativeElement;
    contentWidget?: NodeWidget | null;
    constructor(parent?: NodeWidget) {
        let native;
        if (parent) {
            native = new addon.QScrollArea(parent.native);
        } else {
            native = new addon.QScrollArea();
        }
        super(native);
        this.native = native;
        this.setNodeParent(parent);
        this.setWidgetResizable(true);
    }
    setWidget(widget: NodeWidget): void {
        // react:✓, //TODO:getter
        this.contentWidget = widget;
        this.native.setWidget(widget.native);
        this.contentWidget.setFlexNodeSizeControlled(this.widgetResizable());
    }
    takeWidget(): NodeWidget | null {
        // react:✓
        const contentWidget = this.contentWidget;
        this.contentWidget = null;
        if (contentWidget) {
            this.native.takeWidget();
            return contentWidget;
        }
        return null;
    }
    setWidgetResizable(resizable: boolean): void {
        this.native.setWidgetResizable(resizable);
        if (this.contentWidget) {
            this.contentWidget.setFlexNodeSizeControlled(resizable);
        }
    }
    widgetResizable(): boolean {
        return this.native.widgetResizable();
    }
}
