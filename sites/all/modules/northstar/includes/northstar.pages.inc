<?php

function northstar_wip($string = '') {

  // @todo: Query the db for blocks the user has chosen to show here.
  $output = '<div class="wip"><h2>Under construction!</h2>
    <span>'.$string.'</span></div>';
  
  return $output;
}

function northstar_sites() {
  drupal_set_title('');
  $output = '';
  
  $query = new EntityFieldQuery;

  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->propertyCondition('type', 'site')
//    ->fieldCondition('field_'.$type, 'value', 1, '=')
    ->execute();
  

  $nids = array();
  foreach($result['node'] as $record) {
    $nids[] = $record->nid;
  }
  $nodes = entity_load('node', $nids);

  $output .= '<div class="grid-view">';
  foreach($nodes as $node) {
    $output .= theme('northstar_site_thumb', array('element' => $node));
  }
  
  $output .= '</div>';
  return $output;
}

function northstar_font_stack() {
  $output = 'Aa Bb Cc Dd Ee Ff Gg Hh Ii Jj Kk Ll Mm Nn Oo Pp Qq Rr Ss Tt Uu Vv Ww Xx Yy Zz<br/>';
  $output .= '<strong>Aa Bb Cc Dd Ee Ff Gg Hh Ii Jj Kk Ll Mm Nn Oo Pp Qq Rr Ss Tt Uu Vv Ww Xx Yy Zz</strong>';
  return $output;
}

function northstar_not_found() {
  $output = '<h1>This page hasn\'t been built yet.</h1>';
  $dest = drupal_get_destination();
  $output .= '<a href="#" onclick="history.go(-1);return false;">Return to the previous page</a>.';
  return $output;
}

function northstar_test_activity() {
  $path = drupal_get_path('module', 'northstar');
  drupal_add_js($path . '/js/northstar.activity.js');
  $output = '
      <ul class="test-list">
        <li>
          <a class="test-1" href="#">Create a task with measurable progress</a>
        </li>
        <li>
          <a class="test-2" href="#">Create a task with indeterminate progress</a>
        </li>
      </ul>
      <div class="activity-throbber">
        <div class="bars">
          <div class="btop"></div>
          <div class="bmid"></div>
          <div class="bbot"></div>
        </div>
        <div class="the-count">2</div>
      </div>
      
      <div class="activity-throbber pos">
        <div class="bars">
          <div class="btop"></div>
          <div class="bmid"></div>
          <div class="bbot"></div>
        </div>
        <div class="the-count">2</div>
      </div>
    </div>
  </div>';

  return $output;
}
