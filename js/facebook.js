/**
 * @file facebook.js
 *   Initialize the Javascript SDK.
 */

Drupal.behaviors.facebookInit = function () {
    FB.init({
        appId:  Drupal.settings.facebook.appId,
        status: true,
        cookie: true,
        xfbml:  true
    });
}