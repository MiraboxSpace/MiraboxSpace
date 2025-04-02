// 自定义事件类
class EventPlus {
    constructor() {
        this.event = new EventTarget();
    }
    on(name, callback) {
        this.event.addEventListener(name, e => callback(e.detail));
    }
    send(name, data) {
        this.event.dispatchEvent(new CustomEvent(name, {
            detail: data,
            bubbles: false,
            cancelable: false
        }));
    }
}

// 补零
String.prototype.fill = function () {
    return this >= 10 ? this : '0' + this;
};

// unicode编码转换字符串
String.prototype.uTs = function () {
    return eval('"' + Array.from(this).join('') + '"');
};

// 字符串转换unicode编码
String.prototype.sTu = function (str = '') {
    Array.from(this).forEach(item => str += `\\u${item.charCodeAt(0).toString(16)}`);
    return str;
};

// 全局变量/方法
const $emit = new EventPlus(), $ = (selector, isAll = false) => {
    const element = document.querySelector(selector), methods = {
        on: function (event, callback) {
            this.addEventListener(event, callback);
        },
        attr: function (name, value = '') {
            value && this.setAttribute(name, value);
            return this;
        }
    };
    if (!isAll && element) {
        return Object.assign(element, methods);
    } else if (!isAll && !element) {
        throw `HTML没有 ${selector} 元素! 请检查是否拼写错误`;
    }
    return Array.from(document.querySelectorAll(selector)).map(item => Object.assign(item, methods));
};

// 节流函数
$.throttle = (fn, delay) => {
    let Timer = null;
    return function () {
        if (Timer) return;
        Timer = setTimeout(() => {
            fn.apply(this, arguments);
            Timer = null;
        }, delay);
    };
};

// 防抖函数
$.debounce = (fn, delay) => {
    let Timer = null;
    return function () {
        clearTimeout(Timer);
        Timer = setTimeout(() => fn.apply(this, arguments), delay);
    };
};

// 绑定限制数字方法
Array.from($('input[type="num"]', true)).forEach(item => {
    item.addEventListener('input', function limitNum() {
        if (!item.value || /^\d+$/.test(item.value)) return;
        item.value = item.value.slice(0, -1);
        limitNum(item);
    });
});