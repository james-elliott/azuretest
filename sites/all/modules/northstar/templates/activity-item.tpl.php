<?php

/**
 * @file
 * Default theme implementation to present an activity item.
 *
 * @see template_preprocess_activity_item()
 */
?>
<div class="<?php print $classes; ?>">
  <div class="marker"></div>
  <div class="info">
    <?php print $site; ?>
    <span class="env"><?php print $env; ?></span>
    <span class="timestamp"><?php print $time; ?> by <?php print $username; ?></span>
  </div>
  <div class="event-type"><?php print $type; ?></div>
  <div class="summary"><?php print $summary; ?></div>
  <div class="details">
    <?php if ($body) : ?>
    <a class="show-more" href="#">More details</a>
    <div class="more">
      <?php print $body; ?>
    </div>
    <?php endif; ?>
  </div>
</div>
