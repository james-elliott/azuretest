<?php

function northstar_library_home() {
  $page = array();
  
  $page['search'] = array(
    '#type' => 'container',
    'search_text' => array(
      '#type' => 'textfield',
      '#title' => '',
      '#attributes' => array(
        'placeholder' => 'Search the Library',
      ),
    ),
    'search_button' => array(
      '#type' => 'button',
      '#value' => 'Go',
    ),
    '#attributes' => array(
      'class' => array('library-search'),
    ),
  );
  
  $page['browse'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('split-two'),
    ),
  );
  
  $product_links = array(
    '#title' => 'Browse by Product',
    '#content' => 'Product links go here!',
  );
  
  $page['browse']['doc'] = array(
    '#theme' => 'northstar_container',
    '#title' => 'Browse by Product',
    '#content' => 'Product links go here!',
  );
  
  $page['browse']['kb'] = array(
    '#theme' => 'northstar_container',
    '#title' => 'Featured articles',
    '#content' => 'Put articles here',
  );
  
  return $page;
}
