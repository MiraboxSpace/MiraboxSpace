import { defineStore } from 'pinia';

// 插件钩子
export const usePluginStore = defineStore('pluginStore', () => {
  document.title = window.argv[3].plugin.uuid + ' - 插件';

  // 定时器线程
  const Timer = new Worker('interval.js');
  const TimerSubscribe: { uuid: string; fn: () => void }[] = [];
  Timer.addEventListener('message', ({ data: { event, uuid } }: { data: { event: string; uuid: string } }) => {
    const subIndex = TimerSubscribe.findIndex((item) => item.uuid === uuid);
    subIndex !== -1 && event === 'setInterval' && TimerSubscribe[subIndex].fn();
  });

  // 创建定时器
  const Interval = (uuid: string, delay: number, fn: () => void) => {
    TimerSubscribe.findIndex((item) => item.uuid === uuid) === -1 && TimerSubscribe.push({ uuid, fn });
    Timer.postMessage({ event: 'setInterval', uuid, delay });
  };

  // 销毁定时器
  const Unterval = (uuid: string) => {
    const subIndex = TimerSubscribe.findIndex((item) => item.uuid === uuid);
    subIndex !== -1 && TimerSubscribe.splice(subIndex, 1);
    Timer.postMessage({ event: 'clearInterval', uuid });
  };

  // 连接软件
  const message = ref<StreamDock.Message>();
  const server = new WebSocket('ws://127.0.0.1:' + window.argv[0]);
  server.onopen = () => server.send(JSON.stringify({ event: window.argv[2], uuid: window.argv[1] }));
  server.onmessage = (e) => (message.value = JSON.parse(e.data));

  // 操作数据存储
  class Actions {
    settings: {};
    action: string;
    context: string;
    title: string;
    titleParameters = {} as titleParameters;
    constructor(action: string, context: string, settings: {}) {
      this.action = action;
      this.context = context;
      this.settings = settings;
    }

    // 添加操作
    static list: Actions[] = [];
    static addAction = (action: string, context: string, settings: {}) => {
      const instance = new Actions(action, context, settings);
      this.list.push(instance);
      return instance;
    };

    // 删除操作
    static delAction = (context: string) => {
      const i = this.list.findIndex((item) => item.context === context);
      i !== -1 && this.list.splice(i, 1);
    };

    // 获取操作数据
    static getAction = (context: string) => {
      return Actions.list.find((item) => item.context === context);
    };

    // 获取所有操作数据
    static getActions = (action: string) => {
      return this.list.filter((item) => item.action === action);
    };

    // 通知属性检查器
    sendToPropertyInspector = (payload: any) => {
      server.send(JSON.stringify({ event: 'sendToPropertyInspector', action: this.action, context: this.context, payload }));
    };

    // 切换状态
    setState = (state: number) => {
      server.send(JSON.stringify({ event: 'setState', context: this.context, payload: { state } }));
    };

    // 设置标题
    setTitle = (title: string) => {
      server.send(JSON.stringify({ event: 'setTitle', context: this.context, payload: { title, target: 0 } }));
    };

    // 设置图片
    setImage = (url: string) => {
      if (url.includes('data:')) {
        server.send(JSON.stringify({ event: 'setImage', context: this.context, payload: { target: 0, image: url } }));
        return;
      }
      const image = new Image();
      image.src = url;
      image.onload = () => {
        const canvas = document.createElement('canvas');
        canvas.width = image.naturalWidth;
        canvas.height = image.naturalHeight;
        const ctx = canvas.getContext('2d');
        ctx.drawImage(image, 0, 0);
        server.send(JSON.stringify({ event: 'setImage', context: this.context, payload: { target: 0, image: canvas.toDataURL('image/png') } }));
      };
    };

    // 设置持久化数据
    setSettings = (payload: any) => {
      this.settings = payload;
      server.send(JSON.stringify({ event: 'setSettings', context: this.context, payload }));
    };

    // 默认浏览器打开
    openUrl = (url: string) => {
      server.send(JSON.stringify({ event: 'openUrl', payload: { url } }));
    };
  }

  return {
    message,
    Interval,
    Unterval,
    ActionArr: Actions.list,
    getAction: Actions.getAction,
    addAction: Actions.addAction,
    delAction: Actions.delAction,
    getActions: Actions.getActions
  };
});

// !! 请勿更改此处 !!
type MessageTypes = { plugin: StreamDock.PluginMessage; action: StreamDock.ActionMessage };
export const useWatchEvent = <T extends keyof MessageTypes>(type: T, MessageEvents: MessageTypes[T]) => {
  const plugin = usePluginStore();
  if (type === 'plugin') {
    return watch(
      () => plugin.message,
      () => {
        if (!plugin.message) return;
        if (plugin.message.action) return;
        MessageEvents[plugin.message.event]?.(JSON.parse(JSON.stringify(plugin.message)));
      }
    );
  }
  const Events: StreamDock.ActionMessage = {
    willAppear({ action, context, payload }) {
      !plugin.getAction(context) && plugin.addAction(action, context, payload.settings);
    },
    willDisappear({ context }) {
      plugin.delAction(context);
    },
    didReceiveSettings({ context, payload }) {
      const action = plugin.getAction(context);
      action.settings = payload.settings;
    },
    titleParametersDidChange({ context, payload }) {
      const action = plugin.getAction(context);
      action.title = payload.title;
      action.titleParameters = payload.titleParameters;
    }
  };
  return watch(
    () => plugin.message,
    () => {
      if (!plugin.message) return;
      if (plugin.message.action !== MessageEvents['ActionID']) return;
      const data = JSON.parse(JSON.stringify(plugin.message));
      Events[plugin.message.event]?.(data);
      MessageEvents[plugin.message.event]?.(data);
    }
  );
};
