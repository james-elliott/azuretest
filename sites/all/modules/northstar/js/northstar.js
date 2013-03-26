(function ($) {

Drupal.behaviors.dropDown = {
  attach: function (context, settings) {
    $('.jumplist a.primary', context).once('drop-down', function () {
      $(this).bind('click.dropDown', $(this).next('.drop-down'), Drupal.behaviors.dropDown.dropToggle);
    });
    $('.drop-button .arrow', context).once('drop-down', function () {
      $(this).bind('click.dropDown', $(this).next('.drop-down'), Drupal.behaviors.dropDown.dropToggle);
    });
    $('body').bind('click.dropDown', function() {
      $('.drop-down-processed.open').removeClass('open');
      $('.drop-down:visible').hide();
    });
    $('select').once('select', Drupal.fancySelect.init);
  },
  dropToggle: function (event) {
    event.preventDefault();
    event.stopPropagation();
    var $dropDown = event.data;
    $('.drop-down:visible').not($dropDown).hide();
    if ($dropDown.is(':visible')) {
      $(this).removeClass('open');
      $dropDown.hide();
    } else {
      $(this).toggleClass('open');
      $dropDown.show();
    }
  }
};

Drupal.fancySelect = {
  init: function () {
    var $select = $('<div class="drop-wrapper select"></div>');
    var $dropdown = $('<ul class="drop-down"></ul>');
    var $primary = $(':selected', this);
    
    $('<a class="primary" href="' + $primary.val() + '">' + $primary.text() + '</a>').appendTo($select);
    
    $('option', this).each(function (i, el) {
      var active = $(this).is(':selected') ? 'active' : '';
      $('<li><a class="'+active+'" href="' + $(this).val() + '">' + $(this).text() + '</a></li>').appendTo($dropdown);
    });
    $dropdown.appendTo($select);
    $select.appendTo($(this).parent());
    $('.primary', $select).bind('click', Drupal.fancySelect.toggle);
    $select.width(parseInt($dropdown.outerWidth()) + parseInt($('.primary', $select).css('padding-right')));
    $dropdown.addClass('processed');
    $('a', $dropdown).bind('click', this, Drupal.fancySelect.select);
  },
  select: function (event) {
    event.preventDefault();
    event.stopPropagation();
    var $this = $(this);
    var $select = $(event.data);
    var $dropdown = $this.parents('.drop-down');
    var $selected = $('.primary', $this.parents('.drop-wrapper'));
    
    $selected.attr('href', $this.val()).text($this.text());
    $dropdown.hide();
    $('.active', $dropdown).removeClass('active');
    $this.addClass('active');
    $select.val($this.attr('href')).change();
  },
  toggle: function (event) {
    event.preventDefault();
    event.stopPropagation();
    var $dropdown = $(this).next('.drop-down');
    var $active = $('a.active', $dropdown);
    
    $('.drop-down:visible').not($dropdown).hide();
    $dropdown.toggle();
    var offset = $active.position().top;
    $dropdown.css('top', -offset - 3);
  }
}

})(jQuery);