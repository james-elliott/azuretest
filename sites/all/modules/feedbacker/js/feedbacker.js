(function ($) {

Drupal.behaviors.feedbacker = {
  attach: function (context, settings) {
    $('.feedbacker-toggle', context).once('feedbacker', function() {
      $(this).bind('click', Drupal.feedbacker.toggle);
    });
  }
};

Drupal.feedbacker = Drupal.feedbacker || {};

Drupal.feedbacker.init = function () {
  
};

Drupal.feedbacker.toggle = function (event) {
  event.preventDefault();
  event.stopPropagation();
  var $this = $(event.target);
  $this.toggleClass('enabled');
  if ($this.hasClass('enabled')) {
    $this.text('Disable comments');
    $('html').bind('click', Drupal.feedbacker.add);
    $('html').addClass('comments-on');
  } else {
    $this.text('Enable comments');
    $('html').unbind('click', Drupal.feedbacker.add);
    $('html').removeClass('comments-on');
  }
};

Drupal.feedbacker.add = function (event) {
  console.warn('add comment');
  var $link = $('<a class="comment-anchor" href="feedbacker/add">Comment</a>')
  $link.appendTo('html');
  $link.css({left: event.pageX, top: event.pageY});
};

})(jQuery);