export const useI18nStore = () => {
  const language = window.argv[3].application.language;
  const localString = {
    en: {
      操作选项: 'Operation options'
    },
    zh_CN: {
      操作选项: '操作选项'
    }
  };
  return localString[language] || localString['en'];
};
