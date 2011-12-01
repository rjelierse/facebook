<?php
/**
 * Facebook module: Block related functions.
 */

/**
 * Get the content for the Facebook Events block.
 *
 * @return array
 *     The block content.
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

/**
 * Configure the Facebook Events block settings.
 *
 * @return array
 *     The configuration form.
 */
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

/**
 * Save the configuration settings for the Facebook Events block.
 *
 * @param array $data
 *     The data submitted in the form.
 */
function facebook_block_events_form_submit($data) {
    foreach ($data as $key => $value) {
        variable_set($key, $value);
    }
}

/**
 * Create the block that contains the Facebook Like widget.
 *
 * @return array
 *     The block content.
 */
function facebook_block_like_view() {
    $attributes = array();
    $type = variable_get('facebook_block_like_type', 'button');
    // Check whether to overrule the URL to like.
    $use_facebook_page = variable_get('facebook_block_like_use_page', TRUE);
    $facebook_page = variable_get('facebook_page', '');
    if ($use_facebook_page && !empty($facebook_page)) {
        $attributes['href'] = $facebook_page;
    }
    // Show faces
    $attributes['show_faces'] = variable_get('facebook_block_like_show_faces', TRUE);
    // Color scheme
    $attributes['colorscheme'] = variable_get('facebook_block_like_colorscheme', '');
    // Font
    $attributes['font'] = variable_get('facebook_block_like_font', '');
    // Width
    $attributes['width'] = variable_get('facebook_block_like_width', '');

    // Type specific settings
    switch ($type) {
    case 'button':
        $tag = 'fb:like';
        // Like button layout
        $attributes['layout'] = variable_get('facebook_block_like_button_layout', 'standard');
        // Label for Like button
        $attributes['action'] = variable_get('facebook_block_like_button_verb', 'like');
        // Show Share button
        $attributes['send'] = variable_get('facebook_block_like_button_share', FALSE);
        break;
    case 'box':
        $tag = 'fb:like-box';
        // Show post stream from page
        $attributes['stream'] = variable_get('facebook_block_like_box_stream', FALSE);
        // Show header on box
        $attributes['header'] = variable_get('facebook_block_like_box_header', FALSE);
        // Box border color
        $attributes['border_color'] = variable_get('facebook_block_like_box_color', '');
        break;
    }

    // Return block content
    return array(
        'subject' => t('Like this website'),
        'content' => theme('like_button', $type, $attributes),
    );
}

/**
 * Configuration options for the Facebook Like block.
 *
 * @return array
 *     The configuration form.
 */
function facebook_block_like_form() {
    return array(
        'facebook_block_like_type' => array(
            '#type' => 'radios',
            '#title' => t('Type'),
            '#options' => array(
                'button' => t('Like Button'),
                'box' => t('Like Box'),
            ),
            '#default_value' => variable_get('facebook_block_like_type', 'button'),
        ),
        'facebook_block_like_use_page' => array(
            '#type' => 'checkbox',
            '#title' => t('Like the Facebook page connected to this site instead of the site URL'),
            '#description' => t('The Facebook page can be configured under <a href="@facebook-settings">Facebook Settings</a>.', array('@facebook-settings', url('admin/settings/facebook'))),
            '#default_value' => variable_get('facebook_block_like_use_page', TRUE),
        ),
        'facebook_block_like_show_faces' => array(
            '#type' => 'checkbox',
            '#title' => t('Show the faces of the people that like this item.'),
            '#default_value' => variable_get('facebook_block_like_show_faces', TRUE),
        ),
        'facebook_block_like_colorscheme' => array(
            '#type' => 'select',
            '#title' => t('Color scheme'),
            '#options' => array(
                'light' => t('Light'),
                'dark' => t('Dark'),
            ),
            '#default_value' => variable_get('facebook_block_like_colorscheme', 'light'),
        ),
        'facebook_block_like_font' => array(
            '#type' => 'select',
            '#title' => t('Font'),
            '#options' => array(
                'arial' => 'Arial',
                'lucida grande' => 'Lucida Grande',
                'segoe ui' => 'Segoe UI',
                'tahoma' => 'Tahoma',
                'trebuchet ms' => 'Trebuchet MS',
                'verdana' => 'Verdana'
            ),
            '#default_value' => variable_get('facebook_block_like_font', 'lucida grande'),
        ),
        'facebook_block_like_width' => array(
            '#type' => 'textfield',
            '#title' => t('Width'),
            '#default_value' => variable_get('facebook_block_like_width', ''),
        ),
        'like_button' => array(
            '#type' => 'fieldset',
            '#title' => t('Like button specific settings'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            'facebook_block_like_button_layout' => array(
                '#type' => 'select',
                '#title' => t('Layout'),
                '#options' => array(
                    'standard' => t('Standard'),
                    'button_count' => t('Button count'),
                    'box_count' => t('Box count'),
                ),
                '#default_value' => variable_get('facebook_block_like_button_layout', 'standard'),
            ),
            'facebook_block_like_button_verb' => array(
                '#type' => 'select',
                '#title' => t('Action'),
                '#options' => array(
                    'like' => t('Like'),
                    'recommend' => t('Recommend'),
                ),
                '#default_value' => variable_get('facebook_block_like_button_verb', 'like'),
            ),
            'facebook_block_like_button_share' => array(
                '#type' => 'checkbox',
                '#title' => t('Show an additional Share button.'),
                '#default_value' => variable_get('facebook_block_like_button_share', TRUE),
            ),
        ),
        'like_box' => array(
            '#type' => 'fieldset',
            '#title' => t('Like box specific settings'),
            '#collapsible' => TRUE,
            '#collapsed' => TRUE,
            'facebook_block_like_box_stream' => array(
                '#type' => 'checkbox',
                '#title' => t('Show the feed from the linked page.'),
                '#default_value' => variable_get('facebook_block_like_box_stream', FALSE),
            ),
            'facebook_block_like_box_header' => array(
                '#type' => 'checkbox',
                '#title' => t('Show the box header.'),
                '#default_value' => variable_get('facebook_block_like_box_header', FALSE),
            ),
            'facebook_block_like_box_border_color' => array(
                '#type' => 'textfield',
                '#title' => t('Border color'),
                '#default_value' => variable_get('facebook_block_like_box_border_color', ''),
            ),
        ),
    );
}

/**
 * Save the configuration settings for the Facebook Like block.
 *
 * @param array $data
 *     The data submitted in the form.
 */
function facebook_block_like_form_submit($data) {
    foreach ($data as $key => $value) {
        variable_set($key, $value);
    }
}