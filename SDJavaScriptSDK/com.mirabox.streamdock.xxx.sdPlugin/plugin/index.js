/// <reference path="./utils/common.js" />
/// <reference path="./utils/axios.js" />

const plugin = new Plugins("xxx");

// 操作一
plugin.action1 = new Actions({
    default: {},
    _willAppear({ context }) {
        window.socket.setTitle(context, "Hello world!");
    },
    _willDisappear({ context }) { },
    dialRotate(data) {//旋钮旋转
        console.log(data);
    },
    dialDown(data) {//旋钮按下
        console.log(data);
    }
});