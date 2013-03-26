(function ($) {

Drupal.behaviors.activity = {
  attach: function (context, settings) {
    $('.button, .popup .close', '#block-northstar-activity').bind('click', Drupal.behaviors.activity.activityOpen);
    $('.button, .popup .close', '#block-northstar-activity').bind('contextmenu', Drupal.behaviors.activity.contextOpen);
    Drupal.behaviors.activity.list = $('.popup ul', '#block-northstar-activity');
    $('.create-progress').bind('click', Drupal.behaviors.activity.createProgress);
    $('.create-throbber').bind('click', Drupal.behaviors.activity.createThrobber);
    $('.create-error').bind('click', Drupal.behaviors.activity.createError);
    $('.show-more').bind('click', Drupal.behaviors.activity.toggleMore);
    $('li', '#block-northstar-activity').removeClass('progress new throbber');
    Drupal.behaviors.activity.updateCount();
  },
  activityOpen: function (event) {
    var $button = $('.button-wrapper', '#block-northstar-activity');
    if ($('.popup', $button).length) {
      event.preventDefault();
      event.stopPropagation();
      $button.toggleClass('open');
      $button.siblings('.open').removeClass('open');
      $('.before.done', $button).remove();
      if (!$button.hasClass('open')) {
        $('.new', $button).removeClass('new');
        Drupal.behaviors.activity.updateCount();
        $('body').unbind('click', Drupal.behaviors.activity.activityOpen);
      } else {
        $('body').bind('click', Drupal.behaviors.activity.activityOpen);
      }
    }
  },
  contextOpen: function (event) {
    var $button = $('.button-wrapper', '#block-northstar-activity');
    if ($('.context-menu', $button).length) {
      event.preventDefault();
      event.stopPropagation();
      $button.toggleClass('context');
      $button.siblings('.context').removeClass('context');
      $('.before.done', $button).remove();
      if (!$button.hasClass('context')) {
        $('body').unbind('click', Drupal.behaviors.activity.contextOpen);
      } else {
        $('body').bind('click', Drupal.behaviors.activity.contextOpen);
      }
    }
  },
  hoverNew: function (event) {
    var $this = $(this);
    if (event.type == 'mouseenter') {
      Drupal.behaviors.activity.hoverIntent = setTimeout(function () {
        $this.removeClass('new');
        var $button = $this.closest('.button-wrapper');
        var count = $('.new', $button).length;
        if (count > 0) {
          $('.count', $button).text(count);
          $('.count', $button).show();
        } else {
          $('.count', $button).hide();
        }
      }, 500);
    } else {
      clearTimeout(Drupal.behaviors.activity.hoverIntent);
    }
  },
  createProgress: function (event) {
    event.preventDefault();
    event.stopPropagation();
    var $item = $(Drupal.settings.activity.progress).clone();
    var $marker = $('.marker', $item);
    $item.prependTo(Drupal.behaviors.activity.list);
    var $button = $('.button-wrapper', '#block-northstar-activity');
    $button.removeClass('context').addClass('in-progress');
    $('body').unbind('click', Drupal.behaviors.activity.contextOpen);
    $('<span class="spinner"></span>').prependTo($('.button', $button));
    Drupal.behaviors.activity.updateProgress($item);
  },
  updateProgress: function ($progress) {
    var $marker = $('.marker', $progress);
    var per = 0;
    var run = function () {
      if (per < 100) {
        per = per + Math.random()*17+3;
        if (per >= 100) {
          per = 100;
        }
        $marker.width(per+'%');
        setTimeout(run, Math.random()*800 + 200);
      } else {
        $progress.removeClass('progress').addClass('new');
        $marker.removeAttr('style');
        Drupal.behaviors.activity.updateCount();
        if (Math.random() < .1) {
          $progress.addClass('error');
        }
      }
    }
    setTimeout(run, Math.random()*800 + 200);
  },
  createThrobber: function (event) {
    event.preventDefault();
    event.stopPropagation();
    var $item = $(Drupal.settings.activity.throbber).clone();
    $item.prependTo(Drupal.behaviors.activity.list);
    var $button = $('.button-wrapper', '#block-northstar-activity');
    $button.removeClass('context').addClass('in-progress');
    $('body').unbind('click', Drupal.behaviors.activity.contextOpen);
    $('<span class="spinner"></span>').prependTo($('.button', $button));
    setTimeout(function () {
      $item.removeClass('throbber').addClass('new');
      Drupal.behaviors.activity.updateCount();
      if (Math.random() < .1) {
        $item.addClass('error');
      }
    }, (Math.random()*4000 + 2000));
  },
  updateCount: function () {
    var count = $('.new', '#block-northstar-activity').length > 0 ? $('.new', '#block-northstar-activity').length : '';
    $('.button', '#block-northstar-activity').text(count);
    $('.button-wrapper', '#block-northstar-activity').removeClass('in-progress');
  },
  toggleMore: function (event) {
    if ($(this).hasClass('show')) {
      $(this).removeClass('show').text('More details');
    } else {
      $(this).addClass('show').text('Fewer details');
    }
  },
  hoverIntent: {}
};

})(jQuery);
