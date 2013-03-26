<?php


/**
 * Add messages to the page.
 */
function template_preprocess_feedbacker_dialog(&$variables) {
  drupal_add_css(drupal_get_path('module', 'devdesktop') . '/css/devdesktop_modal.css', array('group' => CSS_THEME));
  if ($_GET['q'] != 'frameclose') {
    $variables['messages'] = theme('status_messages');
  }
}