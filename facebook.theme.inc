<?php
/**
 * Facebook module.
 *
 * @file Contains theme functionality.
 */

/**
 * Theme the Facebook Like button
 *
 * @param string $type
 *     Set the type of Facebook Like widget that should be displayed.
 *     Can be either button or box.
 * @param array $attributes
 *     The attributes to set on the Like widget.
 * @param bool $html5
 *     Render the widget as HTML5 instead of XFBML.
 *
 * @return string
 *     The renderded Like widget.
 */
function theme_like_button($type = 'button', $attributes = array(), $html5 = false) {
    // Set the accepted attributes for the Like button and Like Box.
    $accepted_attributes = array(
        'href',
        'show_faces',
        'colorscheme',
        'font',
        'width'
    );
    $attr5 = array();

    switch ($type) {
    case 'button':
        $accepted_attributes[] = 'layout';
        $accepted_attributes[] = 'action';
        $accepted_attributes[] = 'send';
        $tag = 'fb:like';
        break;
    case 'box':
        $accepted_attributes[] = 'header';
        $accepted_attributes[] = 'stream';
        $accepted_attributes[] = 'border_color';
        $tag = 'fb:like-box';
        break;
    }

    // Clean up attributes
    foreach ($attributes as $name => $value) {
        if (empty($value) || !in_array($name, $accepted_attributes)) {
            unset($attributes[$name]);
            continue;
        }

        $attr5name = 'data-'.str_replace('_', '-', $name);

        switch($name) {
        case 'send':
        case 'show_faces':
            $attributes[$name] = ($value) ? 'true' : 'false';
            $attr5[$attr5name] = ($value) ? 'true' : 'false';
            break;
        default:
            $attr5[$attr5name] = $value;
            break;
        }
    }

    if ($html5) {
        $attr5['class'] = ($type == 'button') ? 'fb-like' : 'fb-like-box';
        return '<div'.drupal_attributes($attr5).'></div>';
    }
    else {
        return "<$tag".drupal_attributes($attributes)."></$tag>";
    }
}