<?php

function northstar_dashboard() {
  // @todo: Query the db for blocks the user has chosen to show here.
  $output = '<div class="split-two">';
  
  $links = array(
    'edit' => array(
      'title' => 'Edit',
      'href' => 'widget/edit',
    ),
    'delete' => array(
      'title' => 'Delete',
      'href' => 'widget/delete',
    ),
    'minimize' => array(
      'title' => 'Minimize',
      'href' => 'widget/minimize',
    ),
  );
  
  $googly_eyes = array(
    '#title' => 'Googly eyes',
    '#content' => '
    <div class="googly-eyes">
      <div class="eyes-1">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-2">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-3">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
    </div>',
    '#links' => $links,
  );
  
  $output .= theme('northstar_container', array('element' => $googly_eyes));
  
  $googly_eyes = array(
    '#title' => 'Googly eyes 2',
    '#content' => '
    <div class="googly-eyes">
      <div class="eyes-1">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-2">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
    </div>',
    '#links' => $links,
  );
  
  $output .= theme('northstar_container', array('element' => $googly_eyes));
  
  $googly_eyes = array(
    '#title' => 'Googly eyes 3',
    '#content' => '
    <div class="googly-eyes">
      <div class="eyes-1">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-2">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-3">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
      <div class="eyes-4">
        <span class="eye left-eye"></span><span class="eye right-eye"></span>
      </div>
    </div>',
    '#links' => $links,
  );
  
  $output .= theme('northstar_container', array('element' => $googly_eyes));
  
  $output .= '</div>';
  
  return $output;
}

function northstar_dashboard_add_widget_form($form, &$form_state, $widget_id) {
  $path = drupal_get_path('module', 'northstar');
  drupal_add_js($path.'/js/northstar.add_widget.js');
  
  if (empty($widget_id)) {
    $form['title']['#markup'] = 'Add widget';
    $form['body']['#markup'] = 'Choose a widget to add to your dashboard.';
    $form['container'] = array(
      '#prefix' => '<div class="widget-list-wrapper">',
      '#suffix' => '</div>',
    );
    $form['container']['search'] = array(
      '#type' => 'textfield',
      '#title' => '',
      '#attributes' => array(
        'class' => array('search-box'),
        'placeholder' => 'Search for widgets',
      ),
      '#size' => 30,
    );

    $form['actions']['#access'] = FALSE;
  
    $query = new EntityFieldQuery;

    $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->propertyCondition('type', 'widget')
      ->execute();


    $nids = array();
    foreach($result['node'] as $record) {
      $nids[] = $record->nid;
    }
    $nodes = entity_load('node', $nids);
    $categories = array();
    $widgets = array();
    foreach($nodes as $node) {
      $node_tids = array();
      // Update the category listing
      foreach($node->field_widget_type[LANGUAGE_NONE] as $tid) {
        $categories[$tid['tid']] = isset($categories[$tid['tid']]) ? $categories[$tid['tid']]+1 : 1;
        $node_tids[] = $tid['tid'];
      }
      $image = field_view_value('node', $node, 'field_screenshot', $node->field_screenshot[LANGUAGE_NONE][0]);
      $output = '
      <span class="image-wrapper">'.render($image).'</span>
      <span class="title">'.$node->title.'</span>
      <span class="description">'.$node->body[LANGUAGE_NONE][0]['value'].'</span>
      <span class="cta">Add this widget</span>
      ';

      $node_terms = entity_load('taxonomy_term', $node_tids);
      $classes = array();
      foreach($node_terms as $term) {
        $classes[] = strtolower($term->name);
      }

      $widgets[] = l($output, $_GET['q'].'/'.$node->nid, array('html' => TRUE, 'attributes' => array('class' => $classes)));
    }

    $form['container']['widgets']['#markup'] = theme('item_list', array('items' => $widgets, 'attributes' => array('class' => array('widget-list clearfix'))));

    $terms = entity_load('taxonomy_term', array_keys($categories));

    $filters = array();
    $filters[] = l('All ('.count($categories).')', $_GET['q'], array('html' => TRUE, 'attributes' => array('class' => array('all'))));
    foreach($categories as $tid => $count) {
      $filters[] = l($terms[$tid]->name.' ('.$count.')', '', array('html' => TRUE, 'attributes' => array('class' => array(strtolower($terms[$tid]->name)))));
    }

    $form['container']['widgets']['#prefix'] = theme('item_list', array('items' => $filters, 'attributes' => array('class' => array('widget-filters'))));
  } else {
    // Stuff for the widget config form goes here.
    $node = node_load($widget_id);
    
    $form['title']['#markup'] = 'Add <em>' . $node->title . '</em> widget';
    $image = field_view_value('node', $node, 'field_screenshot', $node->field_screenshot[LANGUAGE_NONE][0]);
    $form['body']['#markup'] = '
    <div class="widget-details">
    <div class="image-wrapper">'.render($image).'</div>
    <div class="title">'.$node->title.'</div>
    <div class="description">'.$node->body[LANGUAGE_NONE][0]['value'].'</div>
    </div>
    ';
    unset($form['body']['#prefix']);
    unset($form['body']['#suffix']);
    
    $form['widget_options'] = array(
      '#type' => 'fieldset',
      '#title' => 'Widget options',
    );
    $form['widget_options']['intro'] = array(
      '#markup' => '<p>Configure the <em>'.$node->title.'</em> widget. <span class="fake-link">Learn more</span>.</p>',
    );
    $form['widget_options']['options'] = array(
      '#markup' => 'Configuration options for individual widgets will go here.',
    );
    
    $form['actions']['submit']['#value'] = 'Add widget';
    $form['back']['#markup'] = l('back', 'dashboard/add', array('attributes' => array('class' => array('back-link'))));
  }
  
  return $form;
}

