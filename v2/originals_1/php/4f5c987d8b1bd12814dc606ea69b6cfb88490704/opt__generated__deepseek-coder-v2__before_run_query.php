   $oP->add("<form action=\"run_query.php\" method=\"POST\">\n");
   $oP->add("<input type=\"hidden\" name=\"do\" value=\"evaluate\">\n");
   $oP->add("<!-- FORM FIELDS HERE -->\n");
   $oP->add("<input type=\"submit\" value=\"".Dict::S('UI:Button:Evaluate')."\" title=\"".Dict::S('UI:Button:Evaluate:Title')."\">\n");
   $oP->add($oAppContext->GetForForm());
   $oP->add("</form>\n");
   