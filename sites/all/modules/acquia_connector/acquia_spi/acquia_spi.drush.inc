<?php

/**
 * Implements hook_drush_command().
 */
function acquia_spi_drush_command() {
  $items = array();

  $items['acquia-spi-send'] = array(
    'description' => 'Send SPI data to the Acquia Network',
    'aliases' => array('acq-spi')
  );

  return $items;
}

/**
 * Drush callback for acquia-spi-send.
 */
function drush_acquia_spi_send() {
  acquia_spi_send_profile_info();
}
