<?php

function theme_northstar_dropbutton($vars) {
  $element = $vars['element'];
  $links = $element['#links'];
  $type = $element['#type'];
  $classes = isset($element['#classes']) ? $element['#classes'] : array();
  array_unshift($classes, str_replace('_', '-', $type));
  array_unshift($classes, 'drop-wrapper');

  $primary = array_shift($links);
  
  $primary['attributes'] = array('class' => array('primary'));
  
  $output = '<div class="'. implode(' ', $classes).'">';
  $output .= l($primary['title'], $primary['href'], $primary);
  if ($type == 'drop_button') {
    $output .= '<a href="" class="arrow">' . t('more') . '</a>';
  }
  
  if (isset($element['#actions'])) {
    $links['spacer'] = array();
    foreach($element['#actions'] as $key => $action) {
      $links[$key] = $action;
    }
  }

  $output .= theme('links', array('links' => $links, 'attributes' => array('class' => array('drop-down'))));
  
  $output .= '</div>';
  
  return $output;
}

function theme_northstar_select($vars) {
  $element = $vars['element'];
  $options = $element['#options'];
  $classes = isset($element['#classes']) ? $element['#classes'] : array();
  
  $output = '<div class="select '. implode(' ', $classes).'">';
  $output .= l(current($options), '');
  
  $links = array();
  foreach($options as $option) {
    $links[] = array(
      'title' => $option,
      'href' => '',
    );
  };

  $output .= theme('links', array('links' => $links, 'attributes' => array('class' => array('drop-down'))));

  $output .= '</ul></div>';
  
  return $output;
}

function theme_northstar_site_thumb($vars) {
  $node = $vars['element'];
  $type = $node->field_cloud[LANGUAGE_NONE][0]['value'] ? 'cloud' : 'network';
  $image = field_view_value('node', $node, 'field_screen', $node->field_screen[LANGUAGE_NONE][0], 'default');
  $image = drupal_render($image);
  
  $output = '<div class="site-thumb ' . $type . ' grid-item">';
  $output .= l($image, 'mysites/select/'.$node->nid, array('html' => TRUE));
  $output .= '<div class="site-data">';
  $output .= l($node->title, 'mysites/select/'.$node->nid, array('html' => TRUE));
  $output .= '</div>';
  $output .= '</div>';
  
  return $output;
}

function theme_northstar_container($vars) {
  $element = $vars['element'];
  $links = isset($element['#links']) ? array(
      '#type' => 'drop_button',
      '#links' => $element['#links'],
      '#classes' => array('right', 'small'),
    ) : array();
  $classes = array('widget', 'widget-wrapper', 'container');
  if (isset($element['#classes'])) {
    array_merge($classes, $element['#classes']);
  }

  $output  = '<div class="'. implode(' ', $classes).'"><div class="inner">';
  $output .= '<div class="title-bar">';
  $output .= '<span class="title">'. $element['#title'] .'</span>';
  if (count($links) > 0) {
    $output .= drupal_render($links);
  }
  $output .= '</div>
  <div class="content">
    '. $element['#content'] .'
  </div>';
  
  $output .= '</div></div>';
  
  return $output;
}

function template_preprocess_northstar_activity_item(&$vars) {
  $element = $vars['element'];
  $vars['classes_array'][] = 'box';
  $vars['classes_array'][] = 'activity-item';
  if (isset($element->field_status[LANGUAGE_NONE])) {
    foreach($element->field_status[LANGUAGE_NONE] as $value) {
      $vars['classes_array'][] = strtolower($value['value']);
    }
  }
  $vars['classes'] = implode(', ', $vars['classes_array']);

  $site = node_load($element->field_site[LANGUAGE_NONE][0]['target_id']);
  $vars['site'] = l($site->title, 'mysites/select/' . $element->field_site[LANGUAGE_NONE][0]['target_id'], array('attributes' => array('class' => array('subscription'))));
  $vars['site'] = l($site->title, 'node/' . $element->nid . '/edit', array('attributes' => array('class' => array('subscription')), 'query' => array('destination' => 'activity')));
  $vars['env'] = isset($element->field_environment[LANGUAGE_NONE]) ? $element->field_environment[LANGUAGE_NONE][0]['value'] : '';
  $vars['time'] = $ago = format_interval((time() - $element->created) , 1) . t(' ago');
  $account = user_load($vars['element']->uid);
  $name = $account->name;
  if (isset($account->field_first_name[LANGUAGE_NONE][0]['safe_value']) && isset($account->field_last_name[LANGUAGE_NONE][0]['safe_value'])) {
    $name = $account->field_first_name[LANGUAGE_NONE][0]['safe_value'] . ' ' . $account->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  }
  $vars['username'] = l($name, 'user/'.$account->uid, array('html' => TRUE));
  
  $vars['type'] = 'Code deploy';
  $tid = $element->field_filter[LANGUAGE_NONE][0]['tid'];
  $terms = entity_load('taxonomy_term', array($tid));
  $term = array_pop($terms);
  $vars['type'] = ucfirst($term->name);
  $vars['title'] = $element->title;
  $vars['summary'] = isset($element->body[LANGUAGE_NONE]) ? $element->body[LANGUAGE_NONE][0]['summary'] : '';
  $vars['body'] = isset($element->body[LANGUAGE_NONE]) ? $element->body[LANGUAGE_NONE][0]['value'] : '';
//  dsm($vars);
}

function template_preprocess_northstar_notification(&$vars) {
  $element = $vars['element'];
  $vars['classes_array'][] = 'activity-item';
  if (isset($element->field_status[LANGUAGE_NONE])) {
    foreach($element->field_status[LANGUAGE_NONE] as $value) {
      $vars['classes_array'][] = strtolower($value['value']);
    }
  }
  $vars['classes'] = implode(', ', $vars['classes_array']);
  
  $site = node_load($element->field_site[LANGUAGE_NONE][0]['target_id']);
  $vars['site'] = l($site->title, 'mysites/select/' . $element->field_site[LANGUAGE_NONE][0]['target_id'], array('attributes' => array('class' => array('subscription'))));
  $vars['site'] = l($site->title, 'node/' . $element->nid . '/edit', array('attributes' => array('class' => array('subscription')), 'query' => array('destination' => 'activity')));
  $vars['env'] = isset($element->field_environment[LANGUAGE_NONE]) ? $element->field_environment[LANGUAGE_NONE][0]['value'] : '';
  $vars['time'] = $ago = format_interval((time() - $element->created) , 1) . t(' ago');
  $account = user_load($vars['user']->uid);
  $name = $account->name;
  if (isset($account->field_first_name[LANGUAGE_NONE][0]['safe_value']) && isset($account->field_last_name[LANGUAGE_NONE][0]['safe_value'])) {
    $name = $account->field_first_name[LANGUAGE_NONE][0]['safe_value'] . ' ' . $account->field_last_name[LANGUAGE_NONE][0]['safe_value'];
  }
  $vars['username'] = l($name, 'user/'.$account->uid, array('html' => TRUE));
  
  $tid = $element->field_filter[LANGUAGE_NONE][0]['tid'];
  $terms = entity_load('taxonomy_term', array($tid));
  $term = array_pop($terms);
  $vars['type'] = ucfirst($term->name);
  $vars['short'] =isset($element->field_short_description[LANGUAGE_NONE]) ? $element->field_short_description[LANGUAGE_NONE][0]['value'] : '';
  $vars['summary'] = isset($element->body[LANGUAGE_NONE]) ? $element->body[LANGUAGE_NONE][0]['summary'] : '';
  $vars['body'] = isset($element->body[LANGUAGE_NONE]) ? $element->body[LANGUAGE_NONE][0]['value'] : '';
//  dsm($vars);
}
