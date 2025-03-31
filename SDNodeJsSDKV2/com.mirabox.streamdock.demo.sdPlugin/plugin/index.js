const { Plugins, Actions, log, EventEmitter } = require('./utils/plugin');
const { execSync } = require('child_process');

const plugin = new Plugins('demo');


plugin.didReceiveGlobalSettings = ({ payload: { settings } }) => {
    log.info('didReceiveGlobalSettings', settings);
};

const createSvg = (text) => `<svg width="144" height="144" xmlns="http://www.w3.org/2000/svg">
    <text x="72" y="120" font-family="Arial" font-weight="bold" font-size="36" fill="white" text-anchor="middle"
        stroke="black" stroke-width="2" paint-order="stroke">
        ${text}
    </text>
</svg>`;
const timers = {};

plugin.demo = new Actions({
    default: {
    },
    async _willAppear({ context, payload }) {
        // log.info("demo: ", context);
        let n = 0;
        timers[context] = setInterval(async () => {
            const svg = createSvg(++n);
            plugin.setImage(context, `data:image/svg+xml;charset=utf8,${svg}`);
        }, 1000);
    },
    _willDisappear({ context }) {
        // log.info('willDisAppear', context)
        timers[context] && clearInterval(timers[context]);
    },
    _propertyInspectorDidAppear({ context }) {
    },
    sendToPlugin({ payload, context }) {
    },
    keyUp({ context, payload }) {
    },
    dialDown({ context, payload }) {},
    dialRotate({ context, payload }) {}
});