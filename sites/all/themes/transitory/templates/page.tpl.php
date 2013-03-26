<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

 

  <div id="page-wrapper"><div id="page">
  <?php if ($messages): ?>
    <div id="message-wrapper" class="stack-width"><?php print $messages; ?></div>
  <?php endif; ?>
    <div id="top-wrapper" class="fixed-top">
      <div id="header" class="header stack-width"><div class="section clearfix">

        <?php if ($logo || $site_slogan || $site_name): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">      
            <?php if ($site_name): ?>
              <span id="site-name"><?php print $site_name; ?></span>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <span id="site-slogan"><?php print $site_slogan; ?></span>
            <?php endif; ?>
          </a>
        <?php endif; ?>

          <div id="header-left" class="region horizontal blocks-left no-headers">
            <?php print render($page['header_left']); ?>
          </div>

          <div id="header-right" class="region horizontal blocks-right no-headers">
            <?php print render($page['header_right']); ?>
          </div>


      </div></div></div><!-- /.section, /#header -->

      <?php if ($breadcrumb && FALSE): ?>
        <div id="breadcrumb"><?php print $breadcrumb; ?></div>
      <?php endif; ?>

      <div id="title-bar" class="clearfix stack-width">
        <div class="title-wrapper left">
          <?php print render($title_prefix); ?>
          <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
          <?php print render($title_suffix); ?>
        </div>
        <div class="region horizontal left blocks-left no-headers">
          <?php print render($page['titlebar_left']); ?>
        </div>
        <div class="region horizontal right blocks-right no-headers all-caps">
          <?php if ($action_links): ?><ul class="region action-links"><?php print render($action_links); ?></ul><?php endif; ?>
          <?php print render($page['titlebar_right']); ?>
          <?php //<a href="/node/add/event?destination=activity">Add activity item</a> ?>
        </div>
      </div></div>

      <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary'])): ?>
      <div id="tabs" class="section clearfix stack-width">
        <?php print render($tabs); ?>
      </div>
      <?php endif; ?>
    <?php if (!empty($page['content_fixed'])): ?>
    <div id="content-fixed" class="section clearfix stack-width">
      <?php print render($page['content_fixed']); ?>
    </div>
    <?php endif; ?>

    <div id="main-wrapper"><div id="main" class="clearfix">
        
      <?php if (!empty($page['sidebar_left'])): ?>
        <div id="sidebar_left" class="column sidebar left"><div class="section">
          <?php print render($page['sidebar_left']); ?>
        </div></div> <!-- /.section, /#sidebar -->
      <?php endif; ?>
        
      <?php if (!empty($page['sidebar_right'])): ?>
        <div id="sidebar_right" class="column sidebar right"><div class="section">
          <?php print render($page['sidebar_right']); ?>
        </div></div> <!-- /.section, /#sidebar -->
      <?php endif; ?>

      <div id="content" class="column stack-width"><div class="section">
        <a id="main-content"></a>
        <?php print render($page['help']); ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div></div> <!-- /.section, /#content -->

    </div></div> <!-- /#main, /#main-wrapper -->

    <?php if (isset($page['footer_left']) || isset($page['footer_right'])): ?>
    <div id="footer" class="clearfix stack-width">
        <div id="footer-left" class="region horizontal blocks-left no-headers">
          <?php print render($page['footer_left']); ?>
        </div>
        <div id="footer-right" class="region horizontal blocks-right no-headers">
          <?php print render($page['footer_right']); ?>
        </div>
    </div> <!-- /.section, /#footer -->
    <?php endif; ?>
    
  </div></div> <!-- /#page, /#page-wrapper -->
