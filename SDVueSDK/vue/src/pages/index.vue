<!-- 请勿修改此文件 -->
<script setup lang="ts">
  import { NConfigProvider, darkTheme, GlobalThemeOverrides } from 'naive-ui';
  const PropertyInspector = defineAsyncComponent(() => import(`@/pages/actions/${window.argv[4].action.split('.').pop()}.vue`));

  const Theme: GlobalThemeOverrides = {
    Select: {
      peers: {
        InternalSelection: {
          color: '#2D2D2D',
          borderRadius: '0px',
          heightMedium: '30px',
          boxShadowFocus: 'none',
          boxShadowActive: 'none',
          border: '1px solid #7a7a7a',
          borderHover: '1px solid #7a7a7a',
          borderFocus: '1px solid #7a7a7a'
        },
        InternalSelectMenu: {
          height: '140px'
        }
      }
    },
    Input: {
      color: '#2D2D2D',
      borderRadius: '0px',
      heightMedium: '30px',
      boxShadowFocus: 'none',
      border: '1px solid #7a7a7a',
      borderHover: '1px solid #7a7a7a'
    },
    Checkbox: {
      boxShadowFocus: 'none'
    }
  };
</script>

<template>
  <NConfigProvider :theme="darkTheme" :theme-overrides="Theme">
    <PropertyInspector></PropertyInspector>
  </NConfigProvider>
</template>

<style>
  /* 基本样式 */
  * {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
  }
  html,
  body {
    font-size: 9pt;
    color: #e6e6e6;
    user-select: none;
    background-color: #2d2d2d;
    font-family: Arial, sans-serif;
  }

  /* 滚动条样式 */
  ::-webkit-scrollbar {
    width: 0;
  }
  ::-webkit-scrollbar-track {
    border-radius: 8px;
    box-shadow: inset 0 0 6px rgba(0, 0, 0, 0.3);
    -webkit-box-shadow: inset 0 0 6px rgba(0, 0, 0, 0.3);
  }
  ::-webkit-scrollbar-thumb {
    border-radius: 8px;
    background-color: #6d6d71;
    outline: 1px solid slategrey;
  }
</style>
