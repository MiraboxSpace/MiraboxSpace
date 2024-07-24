import { usePluginStore, useWatchEvent } from '@/hooks/plugin';

export default function (name: string) {
  const ActionID = `${window.argv[3].plugin.uuid}.${name}`;

  // 事件侦听器
  const plugin = usePluginStore();
  useWatchEvent('action', {
    ActionID,
    willAppear({ context }) {
      console.log('创建:', context);
    }
  });
}
