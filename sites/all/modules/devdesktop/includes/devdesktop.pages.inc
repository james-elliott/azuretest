<?php

function devdesktop_stack() {
  drupal_set_title('');
  $status = variable_get('stack_status') ? 'Running' : 'Stopped';
  $links = array(
    'configure' => array(
      'title' => 'Configure',
      'href' => 'config',
    ),
  );
  $output = '';

  $output .= '<table class="stack-table">';
  
  $output .= '
  <tr>
    <td class="title">Apache</td>
    <td class="details">
      <table>
        <tr>
          <td class="label">Status</td>
          <td class="value">' . $status . '</td>
        </tr>
        <tr>
          <td class="label">Version</td>
          <td class="value">2.2.1</td>
        </tr>
        <tr>
          <td class="label">Port</td>
          <td class="value">8082</td>
        </tr>
        <tr>
          <td class="label">Modules</td>
          <td class="value">7 enabled</td>
        </tr>
      </table>
    </td>
    <td class="actions">'. theme('links', array('links' => $links, 'attributes' => array('class' => array('hover-buttons')))) . '</td>
  </tr>';
  
  $output .= '
  <tr>
    <td class="title">MySQL</td>
    <td class="details">
      <table>
        <tr>
          <td class="label">Status</td>
          <td class="value">' . $status . '</td>
        </tr>
        <tr>
          <td class="label">Version</td>
          <td class="value">5.1.94</td>
        </tr>
        <tr>
          <td class="label">Port</td>
          <td class="value">36363</td>
        </tr>
        <tr>
          <td class="label">Memcached</td>
          <td class="value">256M</td>
        </tr>
      </table>
    </td>
    <td class="actions">'. theme('links', array('links' => $links, 'attributes' => array('class' => array('hover-buttons')))) . '</td>
  </tr>';
  
  $output .= '
  <tr>
    <td class="title">PHP</td>
    <td class="details">
      <table>
        <tr>
          <td class="version" rowspan="2">5.2</td>
          <td class="label">Mem limit</td>
          <td class="value">256M</td>
        </tr>
        <tr>
          <td class="label">Extensions</td>
          <td class="value">32 enabled</td>
        </tr>
        <tr>
          <td class="version" rowspan="2">5.3</td>
          <td class="label">Mem limit</td>
          <td class="value">512M</td>
        </tr>
        <tr>
          <td class="label">Extensions</td>
          <td class="value">21 enabled</td>
        </tr>
      </table>
    </td>
    <td class="actions">'. theme('links', array('links' => $links, 'attributes' => array('class' => array('hover-buttons')))) . '</td>
  </tr>';
  
  $output .= '</table>';
  
  
  return $output;
}

function devdesktop_togglestack() {
  $status = variable_get('stack_status');
  $place = drupal_get_destination();
  
  variable_set('stack_status', !$status);
  
  drupal_goto($place['destination']);
}

function devdesktop_sync($node) {
  return 'This is where you will sync your site';
}

function devdesktop_frameclose() {
  return '<script>Drupal.devdesktop.frameClose();</script>';
}

function devdesktop_add_site($form, &$form_state) {
  $form_state['step'] = isset($form_state['step']) ? $form_state['step'] : 1; 

  $form_state['storage'] = isset($form_state['storage']) ? $form_state['storage'] : array();
  
  $form_state['storage']['site_method'] = isset($form_state['storage']['site_method']) ? $form_state['storage']['site_method'] : 'distro';
  
  if ($form_state['step'] == 1) {
    drupal_set_title('Choose a method for creating this site');
    $form['method_1'] = array(
      '#type' => 'radio',
      '#title' => 'Install a distribution',
      '#name' => 'site_method',
      '#return_value' => 'distro',
    );
    $form['distro'] = array(
      '#type' => 'select',
      '#title' => 'Choose the distribution to install',
      '#options' => array(
        'd6' => 'Drupal 6',
        'd7' => 'Drupal 7',
        'ad6' => 'Acquia Drupal 6',
        'ad7' => 'Acquia Drupal 7',
        'p6' => 'Pressflow 6',
        'p7' => 'Pressflow 7',
        'op' => 'Open Publish',
        'os' => 'Open Scholar',
      ),
      '#default_value' => 'ad7',
      '#states' => array(
        'visible' => array(
          '[name=site_method]' => array('value' => 'distro'),
        ),
      ),
      '#prefix' => '<div class="indent">',
      '#suffix' => '</div>',
    );
    $form['method_2'] = array(
      '#type' => 'radio',
      '#title' => 'Choose an existing site folder',
      '#name' => 'site_method',
      '#return_value' => 'folder',
    );
    $form['folder'] = array(
      '#type' => 'file',
      '#title' => 'Select the folder where Drupal is',
      '#size' => 20,
      '#states' => array(
        'visible' => array(
          '[name=site_method]' => array('value' => 'folder'),
        ),
      ),
      '#prefix' => '<div class="indent">',
      '#suffix' => '</div>',
    );
    $form['method_3'] = array(
      '#type' => 'radio',
      '#title' => 'Import from Acquia Cloud',
      '#name' => 'site_method',
      '#return_value' => 'cloud',
    );
    $form['user'] = array(
      '#type' => 'container',
      'name' => array(
        '#type' => 'textfield',
        '#title' => 'Enter the e-mail address you use to log into Acquia Cloud',
      ),
      'pass' => array(
        '#type' => 'password',
        '#title' => 'Enter your password',
      ),
      '#states' => array(
        'visible' => array(
          '[name=site_method]' => array('value' => 'cloud'),
        ),
      ),
      '#prefix' => '<div class="indent">',
      '#suffix' => '</div>',
    );
    
    $radios = array(
      'distro' => 'method_1',
      'folder' => 'method_2',
      'cloud' => 'method_3',
    );
    
    $form[$radios[$form_state['storage']['site_method']]]['#default_value'] = $form_state['storage']['site_method'];
    
  }
  
  if ($form_state['step'] == 2) {
    if (in_array($form_state['storage']['site_method'], array('distro', 'folder'))) {
      drupal_set_title('Choose a method of adding a database');
      $form_state['storage']['database_method'] = isset($form_state['storage']['database_method']) ? $form_state['storage']['database_method'] : 'new';
      
      $form['dbm_1'] = array(
        '#type' => 'radio',
        '#title' => 'Create a new database',
        '#return_value' => 'new',
        '#name' => 'database_method',
      );
      $form['dbm_2'] = array(
        '#type' => 'radio',
        '#title' => 'Import from a SQL dump file',
        '#return_value' => 'file',
        '#name' => 'database_method',
      );
      $form['db_file'] = array(
        '#type' => 'file',
        '#title' => 'Select the SQL dump file to import',
        '#size' => 20,
        '#states' => array(
          'visible' => array(
            '[name=database_method]' => array('value' => 'file'),
          ),
        ),
        '#prefix' => '<div class="indent">',
        '#suffix' => '</div>',
      );
      $form['dbm_3'] = array(
        '#type' => 'radio',
        '#title' => 'Import directly from another MySQL server',
        '#return_value' => 'direct',
        '#name' => 'database_method',
      );
      $form['db_remote'] = array(
        '#type' => 'container',
        '#states' => array(
          'visible' => array(
            '[name=database_method]' => array('value' => 'direct'),
          ),
        ),
        '#prefix' => '<div class="indent">',
        '#suffix' => '</div>',
        'db_name' => array(
          '#type' => 'textfield',
          '#title' => 'Database name',
        ),
        'host' => array(
          '#type' => 'textfield',
          '#title' => 'Hostname or IP',
        ),
        'port' => array(
          '#type' => 'textfield',
          '#title' => 'Port',
          '#size' => 5,
        ),
        'name' => array(
          '#type' => 'textfield',
          '#title' => 'MySQL Username',
        ),
        'pass' => array(
          '#type' => 'password',
          '#title' => 'MySQL Password',
        ),
      );
      
      $radios = array(
        'new' => 'dbm_1',
        'file' => 'dbm_2',
        'direct' => 'dbm_3',
      );
      
      $form[$radios[$form_state['storage']['database_method']]]['#default_value'] = $form_state['storage']['database_method'];
      
    } else if ($form_state['storage']['site_method'] == 'cloud') {
      drupal_set_title('Choose a site to import from Acquia Cloud');
      $form['cloud_site'] = array(
        '#type' => 'select',
        '#title' => 'Which site do you want to import?',
        '#options' => array(
          'library',
          'mytestsite',
          'something.about.taco.bell',
        ),
      );

      $form['cloud_env'] = array(
        '#type' => 'select',
        '#title' => 'Choose the environment from this site to mirror',
        '#options' => array(
          'Dev',
          'Stage',
          'Prod',
        ),
      );
    }
  }
  
  if ($form_state['step'] == 3) {
    drupal_set_title('Finish adding site');
    $form['site_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Enter a name for this site',
    );
    $form['site_url'] = array(
      '#type' => 'textfield',
      '#title' => 'Customize the URL for this site (optional)',
    );
    $form['php_version'] = array(
      '#type' => 'select',
      '#title' => 'Which version of PHP should this site use?',
      '#options' => array(
        '5.2',
        '5.3',
      ),
    );
    if (in_array($form_state['storage']['site_method'], array('distro', 'folder'))) {
      $form['add_to_cloud'] = array(
        '#type' => 'checkbox',
        '#title' => 'Connect this site to Acquia Cloud',
      );
    }
  }
  
  $form['prev'] = array(
    '#type' => 'submit',
    '#value' => 'Prev',
    '#access' => $form_state['step'] > 1,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $form_state['step'] < 3 ? 'Next' : 'Add site',
  );
  
  $form['#validate'] = array(
    'devdesktop_add_site_validate',
  );
  
  $form['#submit'] = array(
    'devdesktop_add_site_submit',
  );
  
  return $form;
}

function devdesktop_add_site_validate($form, &$form_state) {
//  dsm($form_state);
  if ($form_state['step'] < 3) {
    $form_state['step'] = $form_state['values']['op'] == 'Prev' ? $form_state['step'] - 1 : $form_state['step'] + 1;
    $form_state['rebuild'] = TRUE;
  }
  
  array_merge($form_state['values'], $form_state['storage']);
  
  if (isset($form_state['input']['site_method'])) {
    $form_state['storage']['site_method'] = $form_state['input']['site_method'];
  }
  if (isset($form_state['input']['database_method'])) {
    $form_state['storage']['database_method'] = $form_state['input']['database_method'];
  }
}

function devdesktop_add_site_submit($form, &$form_state) {
  drupal_goto('frameclose');
}
