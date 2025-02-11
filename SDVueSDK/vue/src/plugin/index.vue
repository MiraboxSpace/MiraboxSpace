<script setup lang="ts">
import { useWatchEvent, usePluginStore } from '@/hooks/plugin';
Object.entries(import.meta.glob('@/plugin/actions/*.ts', { eager: true, import: 'default' })).forEach(([path, fn]) =>
  (fn as Function)(path.replace('/src/plugin/actions/', '').replace('.ts', ''))
);

// 事件侦听器
const plugin = usePluginStore();
useWatchEvent('plugin', {
  deviceDidConnect() { },
  deviceDidDisconnect() { },
  didReceiveGlobalSettings(data) { },
  systemDidWakeUp(data) { },
  applicationDidTerminate(data) {
    console.log(data);
  },
  applicationDidLaunch(data) {
    console.log(data);
  }
});
</script>

<template></template>

<style lang="scss" scoped></style>
