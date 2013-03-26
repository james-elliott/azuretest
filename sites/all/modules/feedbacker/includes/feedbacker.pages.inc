<?php

function northstar_dashboard() {
  
  // @todo: Query the db for blocks the user has chosen to show here.
  $output = '<div class="wip"><span>This page will be a configurable dashboard system similar to ducksboard.com</span></div>';
  
  return $output;
}

function northstar_wip($string = '') {
  
  // @todo: Query the db for blocks the user has chosen to show here.
  $output = '<div class="wip"><h2>Under construction!</h2>
    <span>'.$string.'</span></div>';
  
  return $output;
}

function northstar_sites($type) {
  drupal_set_title('');
  $output = '';
  
  $query = new EntityFieldQuery;

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->propertyCondition('type', 'site')
    ->fieldCondition('field_'.$type, 'value', 1, '=')
    ->execute();
  

  $nids = array();
  foreach($result['node'] as $record) {
    $nids[] = $record->nid;
  }
  $nodes = entity_load('node', $nids);

  $path = $type == 'cloud' ? 'env' : 'overview';
  
  foreach($nodes as $node) {
    $output .= l($node->title, arg(0).'/'.$node->nid.'/'.$path) . '<br/>';
  }
  
  return $output;
}
