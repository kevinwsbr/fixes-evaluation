<div class="<?= htmlspecialchars($sizeClass); ?> ls-flex-column ls-panelboxes-panelbox text-primary">
    <div class="panel panel-primary panel-clickable ls-panelboxes-panelbox-inner selector__<?= strtolower(str_replace(' ', '_', htmlspecialchars($title))); ?>"
        id="panel-<?= htmlspecialchars($position); ?>"
        data-url="<?= htmlspecialchars($url); ?>"
        <?php if ($external): ?>
            data-target="_blank"
        <?php endif; ?>
    >
        <div class="panel-heading">
            <div class="panel-title h4"><?= htmlspecialchars(eT($title)); ?></div>
        </div>
        <div class="panel-body">
            <div class="panel-body-ico">
                <span class="sr-only"><?= htmlspecialchars(eT($title)); ?></span>
                <span class="<?= htmlspecialchars(CHtml::encode($ico)); ?>" style="font-size: 4em"></span>
            </div>
            <div class="panel-body-link">
                <?= htmlspecialchars(eT($description)); ?>
                <?php if ($external): ?>
                    &nbsp;<i class="fa fa-external-link"></i>
                <?php endif; ?>
            </div>
        </div>
    </div>
</div>
