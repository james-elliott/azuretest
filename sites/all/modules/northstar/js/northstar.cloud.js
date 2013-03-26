(function ($) {

Drupal.behaviors.acquiaCloud = {
  attach: function (context, settings) {
    $('#code-dropdown select').change(this.switchBranch);
    this.switchBranch();
  },
  switchBranch: function (event) {
    $('.code-history .entry').each(function () {
      var $this = $(this);
      if ($this.hasClass($('#code-dropdown select').val())) {
        $this.show();
      } else {
        $this.hide();
      }
    })
  }
};

})(jQuery);