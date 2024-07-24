<script setup lang="ts">
  import { usePropertyStore, useWatchEvent, TabView } from '@/hooks/property';
  import { useI18nStore } from '@/hooks/i18n';

  // 事件侦听器
  const i18n = useI18nStore();
  const property = usePropertyStore();
  useWatchEvent({
    didReceiveSettings(data) {},
    sendToPropertyInspector(data) {}
  });
</script>

<template>
  <TabView :label="i18n['操作选项']">...</TabView>
</template>

<style lang="scss" scoped></style>
