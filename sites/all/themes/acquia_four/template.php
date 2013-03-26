<?php

/**
 * Add body classes if certain regions have content.
 */
function acquia_four_preprocess_html(&$variables) {
  // Remove the no-sidebars class added by core
  $variables['classes_array'] = array_filter($variables['classes_array'], 'acquia_four_body_class_filter');
  
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

function acquia_four_body_class_filter($var) {
  return !in_array($var, array('no-sidebars'));
}
