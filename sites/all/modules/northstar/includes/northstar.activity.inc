<?php

function northstar_activity($filter = 'all') {
  $path = drupal_get_path('module', 'northstar');
  drupal_add_js($path . '/js/northstar.activity.js');
  drupal_set_title('Activity');

  $output = '';
  
  $query = new EntityFieldQuery;

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->propertyCondition('type', 'event')
    ->propertyOrderBy('created', 'DESC')
    ->execute();

  if (isset($result['node'])) {
    $nids = array();
    foreach($result['node'] as $record) {
      $nids[] = $record->nid;
    }
    $nodes = entity_load('node', $nids);

    $output .= '<div class="timeline">';
    foreach($nodes as $node) {
      $output .= theme('northstar_activity_item', array('element' => $node, 'view_mode' => 'box'));
    }

    $output .= '</div>';
  }
  return $output;
}
