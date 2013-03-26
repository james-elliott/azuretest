<?php

/**
 * Add body classes if certain regions have content.
 */
function swiss_preprocess_html(&$variables) {
  // Remove the no-sidebars class added by core
  $variables['classes_array'] = array_filter($variables['classes_array'], 'swiss_body_class_filter');

  $arg = arg(0);
  $color = 'blue';
  switch ($arg) {
    case 'dashboard':
      $color = 'red';
      break;
    case 'mysites':
      $color = 'green';
      break;
    case 'library':
      $color = 'orange';
      break;
    case 'support':
      $color = 'light-blue';
      break;
    case 'user':
      $color = 'purple';
      break;
    case 'test':
      $color = 'red';
      break;
  }
  
  $variables['classes_array'][] = $color;
  
  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['sidebar_left'])) {
    $variables['classes_array'][] = 'sidebar-left';
  }
  if (!empty($variables['page']['sidebar_right'])) {
    $variables['classes_array'][] = 'sidebar-right';
  }
}

function swiss_body_class_filter($var) {
  return !in_array($var, array('no-sidebars'));
}
