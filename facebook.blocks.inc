<?php
// $Id$

/**
 * @file facebook.blocks.inc
 *   Block handling functions.
 */

/**
 * Get the content for the Facebook Events block.
 *
 * @return
 *   The block content, or FALSE if an error occurred.
 */
function facebook_block_events_view() {
  $stream = variable_get('facebook_block_events_stream', '');
  // Fallback to Facebook Page setting.
  if (empty($stream)) {
    $stream = variable_get('facebook_page', '');
    $stream = preg_replace('#^(http|https)://www.facebook.com/((pages/.+/)?([a-z0-9\.]+))$#', '$4', $stream);
  }

  if (empty($stream)) {
    return FALSE;
  }

  $settings = array(
      'stream' => $stream,
      'limit' => variable_get('facebook_block_events_limit', 5),
      'offset' => variable_get('facebook_block_events_offset', 0) * 60 * 60 * 1000,
  );

  drupal_add_js(array('facebookEventsBlock' => $settings), 'setting');
  drupal_add_js(drupal_get_path('module', 'facebook') . '/js/facebook-events.js');

  return array(
      'subject' => t('Upcoming events'),
      'content' => '<div id="facebook-events-placeholder"></div>',
  );
}

function facebook_block_events_form() {
  return array(
      'facebook_block_events_stream' => array(
          '#type' => 'textfield',
          '#title' => t('Event stream'),
          '#default_value' => variable_get('facebook_block_events_stream', ''),
          '#description' => t('The id of a Facebook object that has an events feed. Leave blank to use the default Facebook page configured under <a href="@facebook-settings">Facebook Settings</a>.', array('@facebook-settings', url('admin/settings/facebook'))),
      ),
      'facebook_block_events_limit' => array(
          '#type' => 'textfield',
          '#title' => t('Number of items'),
          '#default_value' => variable_get('facebook_block_events_limit', 5),
          '#required' => TRUE,
          '#size' => 5,
      ),
      'facebook_block_events_offset' => array(
          '#type' => 'textfield',
          '#title' => t('Timezone offset'),
          '#default_value' => variable_get('facebook_block_events_offset', 0),
          '#required' => TRUE,
          '#size' => 5,
          '#description' => t('The offset in hours from Pacific Standard Time.'),
      ),
  );
}

function facebook_block_events_form_submit($data) {
  foreach ($data as $key => $value) {
    variable_set($key, $value);
  }
}