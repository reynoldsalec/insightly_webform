<?php

/**
 * Admin settings form.
 *
 * @param $form_id
 *
 * @return
 */
function insightly_webform_form($form_id) {
  $insightly_webform_mapping_settings= variable_get('insightly_webform_mapping_settings', array());
  $insightly_api_key = variable_get('insightly_api_key', '');
  $insightly_api_version = variable_get('insightly_api_version', 'v2');
  $description = <<<EOT
      <p>
      Webform Fields To Insightly Fields Mapping Table <br />
      Required Fields are: Insightly API Key and Insightly API Version
      </p>
EOT;
  $form = array();
  $form['description'] = array(
    '#type' => 'markup',
    '#value' => check_plain($description),
  );
  $form['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Insightly API Key'),
    '#description' => t('The API Key value (shorthand for Organizational Wide Default) is your instance of Insightly.com. That doesn’t show up in very many places, but if you navigate to Setup > Administration Setup > Company Profile > Company Information – you’ll see your API Key listed as a field on that page as well.'),
    '#default_value' => $insightly_api_key,
    '#size' => 15,
    '#required' => TRUE,
  );
  $form['api_version'] = array(
    '#type' => 'radios',
    '#title' => t('Insightly API Version'),
    '#options' => array('v2'),
    '#default_value' => $insightly_api_version,
    '#size' => 70,
    '#required' => TRUE,
  );

  // @TODO: modify this temporary measure when key/value titles get's fixed.
  $form['options_description'] = array(
    '#type' => 'item',
    '#title' => t('Webform Fields to Insightly Fields Mapping Table'),
    '#description' => t('Legend: KEY is the Webform Field Key, VALUE is the Insightly API field name (ex: FIRST_NAME)'),
  );
  $form['options'] = array(
    // @TODO: Figure out a way to change the key/value titles?
    '#type' => 'options',
    '#key_type' => 'custom',
    '#key_type_toggled' => TRUE,
    '#limit' => 200,
    '#optgroups' => FALSE,
    '#options' => $insightly_webform_mapping_settings,
    '#default_value_allowed' => FALSE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}


/**
 * Admin settings form submit handler.
 *
 * @param $form
 * @param $form_state
 *
 * @return
 */
function insightly_webform_form_submit($form, &$form_state) {
  $insightly_webform_mapping_settings = array();
  foreach ($form_state['values']['options']['options'] as $key => $value) {
    if (!empty($key) && !empty($value)) {
      $insightly_webform_mapping_settings[$key] = $value;
    }
  }
  variable_set('insightly_webform_mapping_settings', $insightly_webform_mapping_settings);
  variable_set('insightly_api_key', $form_state['values']['api_key']);
  variable_set('insightly_api_version', $form_state['values']['api_version']);
  variable_set('insightly_webform_debug', $form_state['values']['debug']);
  drupal_set_message(t('Insightly Web2Lead Configuration Settings Saved!'));
}