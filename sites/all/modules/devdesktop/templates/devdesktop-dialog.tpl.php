<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="page-wrapper">
    <div id="header">
      <h1><?php print drupal_get_title(); ?></h1> 
      <a href="#" class="close">Close</a>
    </div>
    <div id="page">
      <?php if (isset($messages)) { print $messages; } ?>
      <?php print render($page['content']); ?>
  </div>
</div> <!-- /#page, /#page-wrapper -->
