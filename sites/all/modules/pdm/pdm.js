(function ($) {

  Drupal.behaviors.PDM = {
    attach : function (context) {

      $("a.pdm-dismiss-link").once('pdm-link').click(function(ev){
        ev.preventDefault();
        $(this).closest(".messages").fadeOut(300);
        var pdm_link = $(this).attr('href');
        if (!pdm_link.match('/#/gi')) {
          $.ajax({
            url: pdm_link
          });
        }
        return false;
      });
    
    }
  }

})(jQuery);
