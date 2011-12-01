<?php
/**
 * Facebook API settings for the entire website.
 *
 * This contains the settings to associate the website with an application or page on Facebook.
 *
 * @return array
 *     The settings form.
 */
function facebook_settings() {
    $form = array(
        'application' => array(
            '#type' => 'fieldset',
            '#title' => t('Application'),
            'facebook_app_id' => array(
                '#type' => 'textfield',
                '#title' => t('Application id'),
                '#default_value' => variable_get('facebook_app_id', ''),
                '#required' => TRUE,
                '#description' => t('To use the Facebook API, you will need to have an application id.'),
            ),
            'facebook_app_secret' => array(
                '#type' => 'textfield',
                '#title' => t('Application secret'),
                '#default_value' => variable_get('facebook_app_secret', ''),
                '#description' => t('To receive access tokens for various actions, an application secret is required. No entering one will limit the functionality of this module.'),
            ),
            'facebook_app_access_token' => array(
                '#type' => 'textfield',
                '#title' => t('Access token'),
                '#value' => variable_get('facebook_app_access_token', ''),
                '#description' => t('This is the access token that has been granted based on the above application id and secret.'),
                '#disabled' => TRUE,
            ),
        ),
        'page' => array(
            '#type' => 'fieldset',
            '#title' => t('Page'),
            'facebook_page' => array(
                '#type' => 'textfield',
                '#title' => t('Page URL'),
                '#default_value' => variable_get('facebook_page', ''),
                '#description' => t('If you want to associate your website with an existing Facebook Page, instead of your website\'s URL, enter the page URL here.'),
            ),
        ),
    );
    return system_settings_form($form);
}

/**
 * Facebook API settings for the Like button on nodes.
 *
 * Contains settings for the method to include the Like button and options to
 * modify the entire layout of the Like button using the SDK.
 *
 * @return array
 *     The settings form.
 */
function facebook_like_settings() {
    $form = array(
        'facebook_node_like_display' => array(
            '#type' => 'select',
            '#title' => t('Diplay'),
            '#description' => t('Where should the like button be displayed.'),
            '#options' => array(
                FACEBOOK_LIKE_INLINE => t('Inside the content of the node'),
                FACEBOOK_LIKE_LINKS => t('In the link section of the node')
            ),
            '#default_value' => variable_get('facebook_node_like_display', FACEBOOK_LIKE_INLINE),
        ),
        'facebook_node_like_dislay_teaser' => array(
            '#type' => 'checkbox',
            '#title' => t('Also show on node teasers.'),
            '#default_value' => variable_get('facebook_node_like_display_teaser', false)
        ),
        'layout' => array(
            '#type' => 'fieldset',
            '#title' => t('Layout'),
            '#collapsible' => true,
            '#collapsed' => true,
            'facebook_node_like_colorscheme' => array(
                '#type' => 'select',
                '#title' => t('Color scheme'),
                '#options' => array(
                    'light' => t('Light'),
                    'dark' => t('Dark'),
                ),
                '#default_value' => variable_get('facebook_node_like_colorscheme', 'light'),
            ),
            'facebook_node_like_font' => array(
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
                '#default_value' => variable_get('facebook_node_like_font', 'lucida grande'),
            ),
            'facebook_node_like_width' => array(
                '#type' => 'textfield',
                '#title' => t('Width'),
                '#default_value' => variable_get('facebook_node_like_width', ''),
            ),
            'facebook_node_like_layout' => array(
                '#type' => 'select',
                '#title' => t('Layout'),
                '#options' => array(
                    'standard' => t('Standard'),
                    'button_count' => t('Button count'),
                    'box_count' => t('Box count'),
                ),
                '#default_value' => variable_get('facebook_node_like_layout', 'standard'),
            ),
            'facebook_node_like_verb' => array(
                '#type' => 'select',
                '#title' => t('Action'),
                '#options' => array(
                    'like' => t('Like'),
                    'recommend' => t('Recommend'),
                ),
                '#default_value' => variable_get('facebook_node_like_verb', 'like'),
            ),
            'facebook_node_like_share' => array(
                '#type' => 'checkbox',
                '#title' => t('Show an additional Share button.'),
                '#default_value' => variable_get('facebook_node_like_share', FALSE),
            ),
        )
    );

    return system_settings_form($form);
}