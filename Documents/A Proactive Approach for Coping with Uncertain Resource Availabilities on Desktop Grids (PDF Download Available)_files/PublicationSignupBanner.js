YUI.add("publicliterature\/stubs\/PublicationSignupBannerContainer.html",function(Y){Y.rg.stubloader.add("publicliterature\/stubs\/PublicationSignupBannerContainer.html", {"compiledTemplate":"function(c,p,i){var _=this;_.b(i=i||\"\");_.b(\"<div id=\\\"\");_.b(_.v(_.f(\"widgetId\",c,p,0)));_.b(\"\\\" \");if(!_.s(_.f(\"displayBanner\",c,p,1),c,p,1,0,0,\"\")){_.b(\"style=\\\"display: none;\\\"\");};_.b(\"> \");_.b(_.t(_.f(\"content\",c,p,0)));_.b(\" <\/div>\");return _.fl();;}","templateString":"<div id=\"{{widgetId}}\" {{^displayBanner}}style=\"display: none;\"{{\/displayBanner}}> {{{content}}} <\/div>"});}, '1.0.0', { requires : ['rg-stubloader']});YUI.add("publicliterature\/stubs\/PublicationSignupBanner.html",function(Y){Y.rg.stubloader.add("publicliterature\/stubs\/PublicationSignupBanner.html", {"compiledTemplate":"function(c,p,i){var _=this;_.b(i=i||\"\");_.b(\"<div id=\\\"\");_.b(_.v(_.f(\"widgetId\",c,p,0)));_.b(\"\\\" class=\\\"signup-banner publication hover-capable\\\"> <div class=\\\"wrapper\\\"> <div class=\\\"collapsed-content headline\\\"> ResearchGate is the professional network for scientists and researchers. <span class=\\\"down-arrow ico-arrow-down-circle\\\"><\/span> <\/div> <div class=\\\"expanded-content\\\"> <div class=\\\"content\\\"> <div class=\\\"indent-left\\\"> <div class=\\\"text-left\\\"> \");if(_.s(_.f(\"option3AuthorsAndNoFT\",c,p,1),c,p,0,399,511,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" The authors of this publication are on ResearchGate but haven't yet made the full-text available for download. \");});c.pop();}_.b(\" \");if(_.s(_.f(\"option2AuthorsAndFT\",c,p,1),c,p,0,562,679,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" The authors of this publication are on ResearchGate and have made the <b>full-text available on their profiles<\/b>. \");});c.pop();}_.b(\" \");if(_.s(_.f(\"option1NoAuthors\",c,p,1),c,p,0,725,799,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" The full-text for this publication is not yet available on ResearchGate. \");});c.pop();}_.b(\" <\/div> <div class=\\\"publication-details\\\"> <ul class=\\\"c-list\\\"> <li class=\\\"c-list-item li-publication\\\" style=\\\"text-align: left;\\\"> <div class=\\\"indent-left\\\"> \");if(_.s(_.f(\"previewUrl\",c,p,1),c,p,0,989,1092,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" <div class=\\\"publication-preview\\\"> <div class=\\\"preview-img\\\"> <img src=\\\"\");_.b(_.v(_.f(\"previewUrl\",c,p,0)));_.b(\"\\\"\/> <\/div> <\/div> \");});c.pop();}_.b(\" \");if(!_.s(_.f(\"previewUrl\",c,p,1),c,p,1,0,0,\"\")){_.b(\" <div class=\\\"fulltext-thumb\\\"> <span class=\\\"publication-preview\\\"><\/span> <\/div> \");};_.b(\" <\/div> <div> <h5> \");if(_.s(_.f(\"type\",c,p,1),c,p,0,1245,1294,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" <span class=\\\"publication-type\\\">\");_.b(_.v(_.f(\"type\",c,p,0)));_.b(\":<\/span> \");});c.pop();}_.b(\" <span class=\\\"publication-title\\\">\");if(_.s(_.f(\"shortenString\",c,p,1),c,p,0,1354,1376,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\"publicationTitle, 180|\");});c.pop();}_.b(\"<\/span> <\/h5> \");if(_.s(_.f(\"source\",c,p,1),c,p,0,1419,1476,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" <span class=\\\"details\\\">Available from: \");_.b(_.v(_.f(\"source\",c,p,0)));_.b(\"<\/span> \");});c.pop();}_.b(\" <\/div> <\/li> <\/ul> <div class=\\\"clear\\\"><\/div> <\/div> <\/div> <div class=\\\"indent-right\\\"> <div class=\\\"text-right\\\"> \");if(_.s(_.f(\"option3AuthorsAndNoFT\",c,p,1),c,p,0,1625,1704,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" Sign up for a free account to <b>request the full-text version<\/b> from them. \");});c.pop();}_.b(\" \");if(_.s(_.f(\"option2AuthorsAndFT\",c,p,1),c,p,0,1755,1833,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" Sign up for a free account to <b>access the full-text version<\/b> from them. \");});c.pop();}_.b(\" \");if(_.s(_.f(\"option1NoAuthors\",c,p,1),c,p,0,1879,1954,\"{{ }}\")){_.rs(c,p,function(c,p,_){_.b(\" Sign up for a free account to <b>request the full-text version<\/b> of it. \");});c.pop();}_.b(\" <\/div> <a href=\\\"signup.SignUp.html?ev=su_banner\\\" class=\\\"btn btn-large btn-fullwidth btn-promote\\\">Join for free<\/a> <\/div> <\/div> <\/div> <\/div> <a class=\\\"ico-x-close-dark js-collapse\\\"><\/a> <\/div>\");return _.fl();;}","templateString":"<div id=\"{{widgetId}}\" class=\"signup-banner publication hover-capable\"> <div class=\"wrapper\"> <div class=\"collapsed-content headline\"> ResearchGate is the professional network for scientists and researchers. <span class=\"down-arrow ico-arrow-down-circle\"><\/span> <\/div> <div class=\"expanded-content\"> <div class=\"content\"> <div class=\"indent-left\"> <div class=\"text-left\"> {{#option3AuthorsAndNoFT}} The authors of this publication are on ResearchGate but haven't yet made the full-text available for download. {{\/option3AuthorsAndNoFT}} {{#option2AuthorsAndFT}} The authors of this publication are on ResearchGate and have made the <b>full-text available on their profiles<\/b>. {{\/option2AuthorsAndFT}} {{#option1NoAuthors}} The full-text for this publication is not yet available on ResearchGate. {{\/option1NoAuthors}} <\/div> <div class=\"publication-details\"> <ul class=\"c-list\"> <li class=\"c-list-item li-publication\" style=\"text-align: left;\"> <div class=\"indent-left\"> {{#previewUrl}} <div class=\"publication-preview\"> <div class=\"preview-img\"> <img src=\"{{previewUrl}}\"\/> <\/div> <\/div> {{\/previewUrl}} {{^previewUrl}} <div class=\"fulltext-thumb\"> <span class=\"publication-preview\"><\/span> <\/div> {{\/previewUrl}} <\/div> <div> <h5> {{#type}} <span class=\"publication-type\">{{type}}:<\/span> {{\/type}} <span class=\"publication-title\">{{#shortenString}}publicationTitle, 180|{{\/shortenString}}<\/span> <\/h5> {{#source}} <span class=\"details\">Available from: {{source}}<\/span> {{\/source}} <\/div> <\/li> <\/ul> <div class=\"clear\"><\/div> <\/div> <\/div> <div class=\"indent-right\"> <div class=\"text-right\"> {{#option3AuthorsAndNoFT}} Sign up for a free account to <b>request the full-text version<\/b> from them. {{\/option3AuthorsAndNoFT}} {{#option2AuthorsAndFT}} Sign up for a free account to <b>access the full-text version<\/b> from them. {{\/option2AuthorsAndFT}} {{#option1NoAuthors}} Sign up for a free account to <b>request the full-text version<\/b> of it. {{\/option1NoAuthors}} <\/div> <a href=\"signup.SignUp.html?ev=su_banner\" class=\"btn btn-large btn-fullwidth btn-promote\">Join for free<\/a> <\/div> <\/div> <\/div> <\/div> <a class=\"ico-x-close-dark js-collapse\"><\/a> <\/div>"});}, '1.0.0', { requires : ['rg-stubloader']});