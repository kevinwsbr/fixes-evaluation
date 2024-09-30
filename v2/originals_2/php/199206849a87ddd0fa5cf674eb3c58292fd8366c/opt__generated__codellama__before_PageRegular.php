protected function buildFooterScripts($objLayout, $objPageOrNull)
{
	$strScripts = '';

	// jQuery
	if ($objLayout->addJQuery)
	{
		$arrJquery = StringUtil::deserialize($objLayout->jquery, true);

		foreach ($arrJquery as $strTemplate)
		{
			if ($strTemplate)
			{
				$objTemplate = new FrontendTemplate($strTemplate);
				$strScripts .= $objTemplate->parse();
			}
		}

		// Add a placeholder for dynamic scripts (see #4203)
		$strScripts .= "[[TL_JQUERY_$nonce]]";
	}

	// MooTools
	if ($objLayout->addMooTools)
	{
		$arrMootools = StringUtil::deserialize($objLayout->mootools, true);

		foreach ($arrMootools as $strTemplate)
		{
			if ($strTemplate)
			{
				$objTemplate = new FrontendTemplate($strTemplate);
				$strScripts .= $objTemplate->parse();
			}
		}

		// Add a placeholder for dynamic scripts (see #4203)
		$strScripts .= "[[TL_MOOTOOLS_$nonce]]";
	}

	// Add the framework-agnostic JavaScripts
	if ($objLayout->scripts)
	{
		$arrScripts = StringUtil::deserialize($objLayout->scripts, true);

		foreach ($arrScripts as $strTemplate)
		{
			if ($strTemplate)
			{
				$objTemplate = new FrontendTemplate($strTemplate);
				$strScripts .= $objTemplate->parse();
			}
		}
	}

	// Add a placeholder for dynamic scripts (see #4203, #5583)
	$strScripts .= "[[TL_BODY_$nonce]]";

	// Add the external JavaScripts
	$arrExternalJs = StringUtil::deserialize($objLayout->externalJs);

	// Get the file entries from the database
	$objFiles = FilesModel::findMultipleByUuids($arrExternalJs);
	$projectDir = System::getContainer()->getParameter('kernel.project_dir');

	if ($objFiles !== null)
	{
		while ($objFiles->next())
		{
			if (file_exists($projectDir . '/' . $objFiles->path))
			{
				$strScripts .= Template::generateScriptTag($objFiles->path, false, null);
			}
		}
	}

	// Add the custom JavaScript
	if ($objLayout->script)
	{
		$strScripts .= "\n" . trim($objLayout->script) . "\n";
	}

	$this->Template->mootools = $strScripts;

	$this->Template->jsonLdScripts = function ()
	{
		if (!$this->responseContext->isInitialized(JsonLdManager::class))
		{
			return '';
		}

		$jsonLd = $this->responseContext->get(JsonLdManager::class);
		$scripts = [];

		foreach ($jsonLd as $item)
		{
			$script = '';

			if (isset($item['head']) && is_array($item['head']))
			{
				foreach ($item['head'] as $tag)
				{
					$script .= 'document.write(\'' . addslashes($tag) . '\');';
				}
			}

			if (isset($item['body']) && is_array($item['body']))
			{
				foreach ($item['body'] as $tag)
				{
					$script .= 'document.write(\'' . addslashes($tag) . '\');';
				}
			}

			if (trim($script) !== '')
			{
				$scripts[] = $script;
			}
		}

		return implode("\n", $scripts);
	};
}
