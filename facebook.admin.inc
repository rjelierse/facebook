<?php
/**
 * Facebook - Administration functions.
 */

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