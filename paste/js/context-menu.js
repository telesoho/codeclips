(function () {
    "use strict";
    function buildContextMenu() {
      var props = {
      };
  
      var ContextMenuComponent = {
        name: 'context-menu',
  
        props: props,
  
        data: function data() {
          return {
              message: "This is Menu",
          };
        },
        template: '<div>{{message}}</div>',
      };

      return ContextMenuComponent;
    }

    if (typeof exports == "object") {
      module.exports = buildContextMenu();
    } else if (typeof define == "function" && define.amd) {
      define(["contextmenu"], function () {
        return buildContextMenu();
      });
    } else if (window && window.Vue) {
      Vue.component('context-menu', buildContextMenu());
    }
})();
