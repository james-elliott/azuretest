<?php

function northstar_env($env) {
  $env = !empty($env) ? $env : 'dev';
  $site = $_GET['site'] ? node_load($_GET['site']) : FALSE;
  $item = menu_get_item();
  $path = $item['path'];
  $destination = $path .'/'.$env;
  
  if (!$site) {
    purl_goto('mysites', array('purl' => array('disabled' => TRUE)));
  }
  
  $output = array(
    'tabs' => array(
      '#prefix' => '<div id="tabs" class="stack-width">',
      '#suffix' => '</div>',
    ),
    'right' => array(
      '#prefix' => '<div><div class="sidebar right">',
      '#suffix' => '</div>',
    ),
    'code' => array(
      '#prefix' => '<div class="code">',
      '#suffix' => '</div></div>',
    ),
  );

  $defaults = array(
    'dev' => 'master',
    'stage' => 'branches/proto',
    'prod' => 'tags/2012-01-30',
  );

  if (!in_array($env, array_keys($defaults))) {
    $env = 'dev';
  }
  
  $links = array();
  foreach($defaults as $key => $branch) {
    $links[$key] = array(
      'title' => ucfirst($key),
      'href' => $path.'/'.$key,
    );
    if ($env == $key) {
      $links[$key]['attributes'] = array(
        'class' => array('active'),
      );
    }
  }
  
  $args = array(
    'links' => $links,
    'attributes' => array('class' => array('tabs', 'primary')),
    'heading' => array(
      'text' => 'Primary tabs',
      'class' => array('element-invisible'),
      'level' => 'h2',
    )
  );
  
  $output['tabs']['#markup'] = theme('links', $args);

  $links = array(
    'update' => array(
      'title' => 'Update',
      'href' => $path.'/update-content/'.$env,
      'query' => array('destination' => $destination),
    ),
    'backup' => array(
      'title' => 'Backup databases',
      'href' => $path.'/backup-dbs/'.$env,
      'query' => array('destination' => $destination),
    ),
    'download' => array(
      'title' => 'Download content',
      'href' => $path.'/download-content/'.$env,
      'query' => array('destination' => $destination),
    ),
  );

  if ($env == 'prod') {
    $links['backup']['title'] = 'Backup';
    unset($links['update']);
  }

  $output['right']['content'] = array(
    '#prefix' => '<div class="group"><h2>'.t('Content').'</h2>',
    'button' => array(
      '#type' => 'drop_button',
      '#links' => $links,
      '#classes' => array('right', 'small'),
    ),
    '#suffix' => '
      <div class="list">
      <h3>Databases</h3>
      <ul>
      <li>acquiadotcom</li>
      <li>argweeya</li>
      </ul>
      </div>
      <div class="list">
      <h3>Files</h3>
      <ul><li>0.25 gb used, 1.75gb remaining</li></ul>
      </div>
      </div>',
  );

  $domains = array(
      'push' => array(
        'title' => $env != 'prod' ? $env.'.acquia.com' : 'www.acquia.com',
        'href' => 'http://'.$env.'.acquia.com',
      ),
      'import' => array(
        'title' => $env.'.acquiadotcom.acquia-sites.com',
        'href' => 'http://'.$env.'.acquiadotcom.acquia-sites.com',
      ),
  );

  $output['right']['domains'] = array(
    '#prefix' => '<div class="group"><h2>'.t('Domains').'</h2>',
    'button' => array(
      '#type' => 'drop_button',
      '#links' => array(
        'update' => array(
          'title' => 'Clear caches',
          'href' => $path.'/cc-all/'.$env,
        'query' => array('destination' => $destination),
        ),
        'add' => array(
          'title' => 'Add domain',
          'href' => $path.'/add-domain/'.$env,
        'query' => array('destination' => $destination),
        ),
        'manage' => array(
          'title' => 'Manage domains',
          'href' => $path.'/manage-domains/'.$env,
        'query' => array('destination' => $destination),
        ),
      ),
      '#classes' => array('right', 'small'),
    ),
    '#suffix' => theme('links', array('links'=> $domains)) . '</div>',
  );

  $output['right']['scripts'] = array(
    '#prefix' => '<div class="group"><h2>'.t('Scripts').'</h2>',
    'button' => array(
      '#type' => 'drop_button',
      '#links' => array(
        'thing' => array(
          'title' => '',
          'href' => '',
        ),
        'add' => array(
          'title' => 'Add script',
          'href' => $path.'/add-script/'.$env,
          'query' => array('destination' => $destination),
        ),
        'manage' => array(
          'title' => 'Manage scripts',
          'href' => $path.'/manage-scripts/'.$env,
          'query' => array('destination' => $destination),
        ),
      ),
      '#classes' => array('right', 'small'),
    ),
    '#suffix' => '
      <ul>
      <li>db scrubber</li>
      <li>selenium test kickoff</li>
      </ul>
      </div>',
  );

  $output['code']['branches'] = array(
    '#type' => 'select',
    '#title' => 'Code',
    '#options' => array(
      'master' => 'master',
      'branches/proto' => 'branches/proto',
      'tags/2011-12-12' => 'tags/2011-12-12',
      'tags/2012-01-30' => 'tags/2012-01-30',
    ),
    '#value' => $defaults[$env],
    '#prefix' => '<div id="code-dropdown" class="content-fixed">',
  );
  
  drupal_add_js(drupal_get_path('module', 'northstar').'/js/northstar.cloud.js');
  
  $output['code']['button'] = array(
    '#type' => 'drop_button',
    '#links' => northstar_code_options($env),
    '#classes' => array('right'),
    '#suffix' => '</div>',
  );
  
  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', 'taxonomy_term')
    ->execute();
  $terms = $result['taxonomy_term'];

  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'commit')
    ->propertyOrderBy('nid', 'DESC')
    ->execute();

  $nids = array();
  foreach($result['node'] as $record) {
    $nids[] = $record->nid;
  }
  $entries = entity_load('node', $nids);

  $history = '';
  foreach($entries as $entry) {
    $author = user_load_by_name($entry->name);
    $classes = array('entry');
    foreach($entry->field_tags[LANGUAGE_NONE] as $term) {
      $full_term = taxonomy_term_load($term['tid']);
      $classes[] = $full_term->name;
    }

    $history .= '
      <div class="'.implode(' ', $classes).'">
        <div class="username">'.theme('username', array('account' => $author)).'</div>
        <div class="body">'.$entry->field_commit_message[$entry->language][0]['safe_value'].'</div>
        <div class="timestamp">'.  format_date($entry->created).'</div>
      </div>
    ';
  }
  
  $output['code']['history'] = array(
    '#markup' => '<div class="code-history">'.$history.'</div>',
  );
  
  return $output;
}

function northstar_code_options($env = 'dev') {
  $options = array();
  
  $path = 'mysites/envs';
  if ($env == 'dev') {
    $options = array(
      'push' => array(
        'title' => 'Push code to Stage',
        'href' => $path.'/update/push/dev/stage',
      ),
      'import' => array(
        'title' => 'Import an existing site',
        'href' => $path.'/import',
      ),
      'install' => array(
        'title' => 'Install Drupal or a distribution',
        'href' => $path.'/install',
      ),
      'dev' => array(
        'title' => 'Enable live development mode',
        'href' => $path.'/live_dev',
      ),
    );
  } else if ($env == 'stage') {
    $options = array(
      'update' => array(
        'title' => 'Update from Dev',
        'href' => $path.'/update/pull/dev/stage',
      ),
      'push' => array(
        'title' => 'Push code to Prod',
        'href' => $path.'/update/push/stage/prod',
      ),
    );
  } else if ($env == 'prod') {
    $options = array(
      'update' => array(
        'title' => 'Update from Stage',
        'href' => $path.'/update/pull/stage/prod',
      ),
      'push' => array(
        'title' => 'Update from Dev',
        'href' => $path.'/update/pull/dev/prod',
      ),
    );
  }
  
  foreach($options as &$option) {
    $option['query'] = array('destination' => $path.'/'.$env);
  }
   
  return $options;
}

function northstar_update_code_form($form, $form_state, $direction, $source, $destination) {
  $site = isset($_GET['site']) ? node_load($_GET['site']) : FALSE;
  if (!$site) {
    purl_goto('mysites', array('purl' => array('disabled' => TRUE)));
  }
  
  $defaults = array(
    'dev' => 'master',
    'stage' => 'branches/proto',
    'prod' => 'tags/2012-01-30',
  );
  
  $src = isset($form_state['storage']['source']) ? $form_state['storage']['source'] : array(
    'path' => $source,
    'name' => ucfirst($source),
    'branch' => $defaults[$source],
  );
  $dest = isset($form_state['storage']['destination']) ? $form_state['storage']['destination'] : array(
    'path' => $destination,
    'name' => ucfirst($destination),
    'branch' => $defaults[$destination],
  );

  if ($direction == 'push') {
    $dest['new_tag'] = TRUE;
    $dest['branch'] = 'tags/'. date('Y-m-d');
  }
  
  $form['title']['#markup'] = $direction == 'pull' ? 'Update '. $dest['name'] . ' with code from ' . $src['name'] : 'Push code from '.$src['name'].' to '.$dest['name'];

  $text = 'This will update <strong>'. $dest['name'] . '</strong> with the code from <strong>' . $src['name'] . '</strong>';
  if (isset($dest['new_tag'])) {
    $text = 'This will copy the code in 
    <strong>' . $src['branch'] . '</strong> on <strong>'. $src['name'] . '</strong>
    to a new tag
    <strong>'. $dest['branch'] . '</strong> on <strong>' . $dest['name'] . '</strong>';
  }
  
  $form['body']['#markup'] = $text;
  
  $form['actions']['submit']['#value'] = $direction == 'pull' ? 'Update ' . $dest['name'] : 'Push code to ' . $dest['name'];
  
  $form_state['storage']['source'] = $src;
  $form_state['storage']['destination'] = $dest;
  $form_state['storage']['direction'] = $direction;

  return $form;
}

function northstar_update_code_form_submit($form, &$form_state) {
  $output = '';
  $new = isset($form_state['storage']['destination']['new_tag']) ? 'a new tag ' : '';

  $output .= 'Moved code from <strong>'. $form_state['storage']['source']['name'] . '</strong>';
  $output .= ' to ' . $new .'<strong>'. $form_state['storage']['destination']['branch'] . '</strong>';
  $output .= ' on <strong>'. $form_state['storage']['destination']['name'] . '</strong>';

  drupal_set_message($output);
  
  $redirect = isset($form_state['storage']['direction']) && $form_state['storage']['direction'] == 'pull' ? $form_state['storage']['destination']['path'] : $form_state['storage']['source']['path'];
  
  $form_state['redirect'] = 'mysites/envs/'.$redirect;
}

function northstar_toggle_live_dev_form($form, &$form_state) {
  $d = drupal_get_destination();
  $form['title']['#markup'] = 'Enable live development mode';
  $form['body']['#markup'] = 'Enable live development to directly edit the code in your Dev environment.
    Access your code in <strong>~/dev/live_dev</strong> on <strong>srv-5.bjaspan.hosting.acquia.com</strong>. '.
    l('Learn more', $d['destination']);
  $form['actions']['submit']['#value'] = 'Enable';
  
  return $form;
}

function northstar_toggle_live_dev_form_submit($form, &$form_state) {
  dsm('Live development enabled');
}

function northstar_import_site_form($form, &$form_state) {
  unset($form['body']);
  
  $form['title']['#markup'] = 'Import an existing site';
  $form['actions']['submit']['#value'] = 'Import site';
  
  $form['body'] = array();
  
  $form['body']['header'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => 'Import an existing Drupal site\'s code, files, and database into your Dev environment.'
  );
  
  $form['body']['url'] = array(
    '#type' => 'textfield',
    '#title' => 'Site URL',
    '#description' => 'Enter the URL or drag and drop a Drush site archive of the site you want to import.',
  );
  
  return $form;
}

function northstar_import_site_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['url']) || !$form_state['values']['url']) {
    form_set_error('url', 'You must enter a site URL to import.');
  }
}

function northstar_import_site_form_submit($form, &$form_state) {
  dsm('Site imported successfully');
}

function northstar_install_site_form($form, &$form_state, $selected) {
  $path = drupal_get_path('module', 'northstar').'/images/';
  
  $form['title']['#markup'] = 'Install Drupal or a distribution';
  
  $distros = array(
    'ad7' => array(
      'title' => 'Acquia Drupal 7',
      'description' => 'Perfect for self-contained site development with a Drupal 7 twist.',
      'image_path' => 'default.png',
    ),
    'drupal7' => array(
      'title' => 'Drupal 7',
      'description' => 'The new hotness.  Drupal 7 is the latest major release of the Drupal platform.',
      'image_path' => 'default.png',
    ),
    'commons7' => array(
      'title' => 'Drupal Commons',
      'description' => 'Drupal brings people together; Commons gives them something to do.',
      'image_path' => 'commons.png',
    ),
    'oa7' => array(
      'title' => 'Open Atrium',
      'description' => 'Team collaboration tool with a kick of open source awesomesauce.',
      'image_path' => 'open_atrium.png',
    ),
    'op7' => array(
      'title' => 'Open Publish',
      'description' => 'OpenPublish was created to let news publishers “bridge the gap”.',
      'image_path' => 'open_publish.png',
    ),
    'os7' => array(
      'title' => 'Open Scholar',
      'description' => 'A full-featured open-source solution designed for the academic community.',
      'image_path' => 'open_scholar.png',
    ),
    'pressflow7' => array(
      'title' => 'Pressflow 7',
      'description' => 'Integrated performance, scalability, availability, and testing enhancements for Drupal 7.',
      'image_path' => 'pressflow.png',
    ),
    'tattler7' => array(
      'title' => 'Tattler',
      'description' => 'Semantic mining of news and trends.',
      'image_path' => 'tattler.png',
    ),
  );
  $form_state['storage']['distros'] = $distros;
  
  $links = array();
  foreach($distros as $key => $distro) {
    $links[$key] = array(
      'title' => '<span class="title">'.$distro['title'].'</span><span class="description">'.$distro['description'].'</span>',
      'href' => 'mysites/envs/install/'.$key,
      'html' => TRUE,
      'attributes' => array(
        'style' => 'background-image: url(/'.$path.$distro['image_path'].');',
        'class' => $key == $selected ? array('active') : array(),
      ),
      'query' => array_merge(drupal_get_destination(), array('distro' => $key)),
    );
  }
  
  $form['distro'] = array(
    '#type' => 'hidden',
    '#suffix' => !empty($selected) ? '' : theme('links', array('links' => $links, 'attributes' => array('class' => array('distros', 'clearfix')))),
    '#default_value' => $selected,
  );
  
  if ($selected) {
    $form['back']['#markup'] = l('back', 'mysites/envs/install', array('attributes' => array('class' => array('back-link'))));
    $form['body']['#markup'] = 'This will install ' . $distros[$selected]['title'] . ' on your Dev environment.  Any code or content you might have already added to Dev will be erased.';
  } else {
    unset($form['body']);
    $form['actions']['submit']['#access'] = FALSE;
  }
  return $form;
}

function northstar_install_site_form_validate($form, &$form_state) {
  if (empty($form_state['values']['distro'])) {
    form_set_error('distro', 'Please choose a distribution to install.');
  } else {
    drupal_set_message('Successfully installed ' . $form_state['storage']['distros'][$form_state['values']['distro']]['title']. '.');
  }
}

function northstar_update_content_form($form, &$form_state, $env) {
  unset($form['body']);
  $form_state['storage'] = array(
    'env' => $env,
  );
  
  $defaults = array(
    'dev' => 'Dev',
    'stage' => 'Stage',
    'prod' => 'Prod',
  );
  unset($defaults[$env]);
  
  $form['title']['#markup'] = 'Update content on ' . ucfirst($env);
  $form['body']['#markup'] = 'Update <strong>'.ucfirst($env).'</strong> with the database and files from another environment';
  $form['env'] = array(
    '#type' => 'select',
    '#options' => $defaults,
    '#title' => 'Copy content from',
  );
  
  $form['files'] = array(
    '#type' => 'checkbox',
    '#title' => 'Include user-generated files',
    '#default_value' => TRUE,
  );
  
  return $form;
}

function northstar_update_content_form_validate($form, &$form_state) {
  
  $output = 'Copying content ';
  if ($form_state['values']['files']) {
    $output .= 'and files ';
  }
  $output .= 'from <strong>'.ucfirst($form_state['values']['env']).'</strong> to <strong>'.ucfirst($form_state['storage']['env']).'</strong>.';
  
  drupal_set_message($output);
}

function northstar_backup_db_form($form, &$form_state, $env) {
  unset($form['body']);
  $form_state['storage'] = array(
    'env' => $env,
  );
  
  $form['title']['#markup'] = 'Backup databases on ' . ucfirst($env);
  $form['dbs'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'acquiadotcom' => 'acquiadotcom',
      'argweeya' => 'argweeya',
    ),
    '#default_value' => array(
      'acquiadotcom' => 'acquiadotcom',
      'argweeya' => 'argweeya',
    ),
    '#title' => 'Choose the databases to be backed up on <strong>'.ucfirst($env).'</strong>',
  );
  
  return $form;
}

function northstar_backup_db_form_validate($form, &$form_state) {
  $output = 'Backing up databases on <strong>'.ucfirst($form_state['storage']['env']).'</strong>.';
  
  drupal_set_message($output);
}
