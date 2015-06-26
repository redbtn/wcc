<?php
// $Id: openwysiwyg.settings.inc,v 1.2 2009/06/25 16:26:36 thenicespider Exp $
/**
 * @file
 * Settings page callback file for the openwysiwyg module.
 */

/**
 * Menu callback;
 */
 
function openwysiwyg_admin_settings() {
  $form = array();
  // only administrators can access this function
  
  // Generate the form - settings applying to all patterns first
  $form['openwysiwyg_general'] = array(
  '#type' => 'fieldset',
  '#title' => t('General settings'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
  $form['openwysiwyg_general']['openwysiwyg_xhtml'] = array(
  '#type' => 'checkbox',
  '#title' => t('Use xHTML markup'),
  '#default_value' => variable_get("openwysiwyg_xhtml", '0'),
  '#description' => t('Choose whether xhtml markup should be enabled or not.'),
  );
  $form['openwysiwyg_general']['openwysiwyg_editor_width'] = array(
  '#type' => 'textfield',
  '#title' => t('Editor width'),
  '#default_value' => variable_get('openwysiwyg_editor_width', '100%'),
  '#description' => t("Width of the openwysiwyg editor (%,px,em), i.e: 520px"),
  );  
  $form['openwysiwyg_general']['openwysiwyg_editor_height'] = array(
  '#type' => 'textfield',
  '#title' => t('Editor height'),
  '#default_value' => variable_get('openwysiwyg_editor_height', 0),
  '#description' => t("Height of the openwysiwyg editor (%,px,em,ex)"),
  );
  
  $form['openwysiwyg_general']['openwysiwyg_style'] = array(
    '#type' => 'textfield',
    '#title' => t('Stylesheet'),
    '#default_value' => variable_get('openwysiwyg_style', 'openwysiwyg.css'),
    '#description' => t("CSS file for openwysiwyg. File should be located at: <b>openwysiwyg/library/styles/</b>")
  );
  
  $form['openwysiwyg_toolbar1'] = array(
  '#type' => 'fieldset',
  '#title' => t('Toolbar 1 buttons'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
  $form['openwysiwyg_toolbar1']['openwysiwyg_toolbar_buttons_1'] = array(
  '#suffix' => _openwysiwyg_settings_toolbar_js(),
  '#title' => t('Buttons for Toolbar 1'),
  '#type' => 'textfield',
  '#default_value' => variable_get('openwysiwyg_toolbar_buttons_1', 'bold italic underline strikethrough seperator unorderedlist orderedlist'),
  '#description' => t("Specify the names of the buttons to show on the toolbar. They will appear in order. Use the '|' (seperator) to separate button groups."),
  '#prefix' => _openwysiwyg_settings_toolbar(1),
  );
  
  $form['openwysiwyg_toolbar2'] = array(
  '#type' => 'fieldset',
  '#title' => t('Toolbar 2 buttons'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
  $form['openwysiwyg_toolbar2']['openwysiwyg_toolbar_buttons_2'] = array(
  '#title' => t('Buttons for Toolbar 2'),
  '#type' => 'textfield',
  '#default_value' => variable_get('openwysiwyg_toolbar_buttons_2', 'subscript superscript seperator removeformat seperator inserttable insertimage'),
  '#prefix' => _openwysiwyg_settings_toolbar(2),
  );
  return system_settings_form($form);
}


function openwysiwyg_settings_custombuttons() {
  //$form = array();
  
	$data = variable_get("openwysiwyg_custombuttons", NULL);
  // initialize empty last row
  $data[] = array('btnname' => '', 'btnvalue' => '');
  
  $form['openwysiwyg_custombuttons'] = array('#tree' => TRUE,);
  foreach ($data as $key => $val) {
    $form['openwysiwyg_custombuttons'][$key]['btnname'] = array(
      '#type' => 'textfield',
      '#default_value' => $val['btnname'],
      '#size' => 20,
      '#maxlength' => 20,
    );
    $form['openwysiwyg_custombuttons'][$key]['btnvalue'] = array(
      '#type' => 'textfield',
      '#default_value' => $val['btnvalue'],
      '#size' => 50,
      '#maxlength' => 255,
    );
    $form['openwysiwyg_custombuttons'][$key]['delete'] = array(
      '#type' => 'checkbox',
      '#return_value' => 1,
      '#default_value' => 0,
    );
  }
  return system_settings_form($form);
}

function openwysiwyg_settings_visibility() {
  //$form = array();
   
  $form['openwysiwyg_visibility'] = array(
  '#type' => 'fieldset',
  '#title' => t('Visibility settings'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
  $form['openwysiwyg_visibility']['openwysiwyg_textarea_id'] = array(
  '#type' => 'radios',
  '#title' => t('Textarea ID'),
  '#default_value' => variable_get('openwysiwyg_textarea_id', 1),
  '#options' => array(
  t("Don't show openwysiwyg editor on this textareas ID:"),
  t("Only show openwysiwyg editor on this textareas ID:")),
  );
  $form['openwysiwyg_visibility']['openwysiwyg_textarea_id_val'] = array(
  '#type' => 'textfield',
  '#default_value' => variable_get('openwysiwyg_textarea_id_val', 'edit-teaser,edit-body'),
  '#description' => t("Specify the textarea IDs for this rule. Separate by comma."),
  );
  
  $form['openwysiwyg_visibility']['openwysiwyg_content_type'] = array(
  '#type' => 'radios',
  '#title' => t('Content type'),
  '#default_value' => variable_get('openwysiwyg_content_type', 1),
  '#options' => array(
  t("Don't show openwysiwyg editor on this content type:"),
  t("Only show openwysiwyg editor on this content type:")),
  );
  $form['openwysiwyg_visibility']['openwysiwyg_content_type_val'] = array(
  '#type' => 'textfield',
  '#default_value' => variable_get('openwysiwyg_content_type_val', 'page'),
  '#description' => t("Specify the content type for this rule. Separate by comma."),
  );   
  
  $form['openwysiwyg_visibility']['openwysiwyg_comment'] = array(
  '#type' => 'radios',
  '#title' => t('Comment box'),
  '#default_value' => variable_get('openwysiwyg_comment', 0),
  '#options' => array(
  t("Disable editor for Comment"), t("Enable editor for Comment")),
  );
  
  $form['openwysiwyg_visibility']['openwysiwyg_page'] = array(
  '#type' => 'radios',
  '#title' => t('Show editor on specific pages'),
  '#default_value' => variable_get('openwysiwyg_page', 0),
  '#options' => array(
  t("Show on every page except the listed pages."),
  t("Show on only the listed pages."),
	t("Show if the following PHP code returns TRUE (PHP-mode, experts only).")),
  );
  $form['openwysiwyg_visibility']['openwysiwyg_page_val'] = array(
  '#type' => 'textarea',
  '#default_value' => variable_get('openwysiwyg_page_val', ''),
  '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page. If the PHP-mode is chosen, enter PHP code between <?php ?>. Note that executing incorrect PHP-code can break your Drupal site."),
  );
  
	return system_settings_form($form);
}

function openwysiwyg_settings_file_browser() {
  //$form = array();
  
  $form['openwysiwyg_file_browser'] = array(
  '#type' => 'fieldset',
  '#title' => t('File Browser'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
  
  $form['openwysiwyg_file_browser']['openwysiwyg_folder_format'] = array(
  '#type' => 'textfield',
  '#title' => t('Folder format for each users'),
  '#default_value' => variable_get('openwysiwyg_folder_format', 'u[uid]'),
  '#description' => t("<ul><li>Specify the format for user folder, if you enter 'u[uid]' then the user folder become files/u1, files/u2, files/u3, etc.</li>".
	"<li>Available variables: <b>[uid]</b> = User ID, <b>[username]</b> = Username, <b>[domainname]</b> = Domain Name</li>".
	"<li>For Drupal multisite please use [domainname]-[username] to avoid conflict for same Username in different site.</li></ul>"),
  );
  $form['openwysiwyg_file_browser']['openwysiwyg_predefine_folder'] = array(
  '#type' => 'textfield',
  '#title' => t('Predefine folder for each users'),
  '#default_value' => variable_get('openwysiwyg_predefine_folder', ''),
  '#description' => t("Specify the predefine folder, i.e: if you enter 'article,story'' then this module will automatically create 'article and story' folder for each users, i.e: files/u1/article and files/u1/story"),
  );  
  
  $form['openwysiwyg_file_upload'] = array(
  '#type' => 'fieldset',
  '#title' => t('File Upload'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
	$form['openwysiwyg_file_upload']['openwysiwyg_file_extension'] = array(
  '#type' => 'textfield',
  '#title' => t('Allowed upload file extensions'),
  '#default_value' => variable_get('openwysiwyg_file_extension', ''),
  '#description' => t("Specify the file extension for upload, i.e: .gif,.jpg, .png . Leave blank if you allow all file extensions."),
  ); 
  $form['openwysiwyg_file_upload']['openwysiwyg_file_size'] = array(
  '#type' => 'textfield',
  '#title' => t('Maximum file size (KB)'),
  '#default_value' => variable_get('openwysiwyg_file_size', '0'),
  '#description' => t("Specify the maximum file size for upload in KB. Set 0 for unlimited size."),
  ); 
	$form['openwysiwyg_file_upload']['openwysiwyg_image_dimension'] = array(
  '#type' => 'textfield',
  '#title' => t('Maximum image dimension'),
  '#default_value' => variable_get('openwysiwyg_image_dimension', '480x480'),
  '#description' => t("Specify the maximum image dimension, i.e: 200x300. If the image size bigger then this module will automatically resize to this value with proportional size (retain image aspect ratio). Leave blank if you don't need this field."),
  );   
  
  $form['openwysiwyg_file_resize'] = array(
  '#type' => 'fieldset',
  '#title' => t('File Resize'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
  );
	$form['openwysiwyg_file_resize']['openwysiwyg_file_resize_width'] = array(
  '#type' => 'textfield',
  '#title' => t('Default resize width'),
  '#default_value' => variable_get('openwysiwyg_file_resize_width', '100'),
  '#description' => t("Specify the default width for image resizing."),
  ); 
  $form['openwysiwyg_file_resize']['openwysiwyg_file_resize_height'] = array(
  '#type' => 'textfield',
  '#title' => t('Default resize height'),
  '#default_value' => variable_get('openwysiwyg_file_resize_height', ''),
  '#description' => t("Specify the default height for image resizing.<br><b>NOTE</b>: If you set value for <b>width</b> and leave <b>height</b> as blank then image will be resizing proportional to width size, and vice versa."),
  ); 
	return system_settings_form($form);
}