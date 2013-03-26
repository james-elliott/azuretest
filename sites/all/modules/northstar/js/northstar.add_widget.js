(function ($) {

Drupal.behaviors.add_widget = {
  attach: function (context, settings) {
    $('.widget-filters a', context).bind('click', function (e) {
      e.preventDefault();
      $('.widget-filters a').removeClass('active');
      var $this = $(e.target);
      $('.widget-list a').parent().show();
      if ($this.attr('class') != 'all') {
        $('.widget-list a:not(.'+$this.attr('class')+')').parent().hide();
      }
      $this.addClass('active');
    });
    
    $('.widget-filters, .widget-list', context).css('min-height', $('.widget-list', context).height()+'px');
  }
};

})(jQuery);
