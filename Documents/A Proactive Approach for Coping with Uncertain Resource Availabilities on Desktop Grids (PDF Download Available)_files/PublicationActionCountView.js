YUI.add("rg.views.publicliterature.PublicationRelationsView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationRelationsView=a.Base.create("publicliterature.PublicationRelationsView",a.rg.WidgetView,[],{events:{global:{relationDeleted:"relationDeleted"}},relationDeleted:function(){var a=this.get("container"),b=a.one(".c-pub-related-items-count"),c=b.getContent().match(/\d+/)[0],d=c-1;"0"==d?this.destroy(!0):b.setContent("("+d+")")}})},"1.0.0",{requires:["rg-confirm","rg-tooltip"]});
YUI.add("rg.views.publicliterature.PublicationRelationsItemView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationRelationsItemView=a.Base.create("publicliterature.PublicationRelationsItemView",a.rg.WidgetView,[],{events:{".pub-relations-delete":{click:"deleteRelation"}},afterRendered:function(){var b=this.get("container"),c=b.one(".pub-relations-preview"),d=b.one(".tooltip-content"),e=d.getContent();c.plug(a.rg.widget.TooltipPlugin,{content:e,align:"bottom"})},deleteRelation:function(){var b=this;a.rg.confirm({header:"Remove supplementary resource relation",body:"Are you sure you want to remove the link between this supplementary resource and its publication? No publications will be removed from your ResearchGate profile.",buttons:[{id:"confirm",label:"Remove relation"},{id:"cancel",label:"Cancel"}],callback:function(c){if("confirm"===c){var d={sourceUid:b.data.sourceUid,targetUid:b.data.targetUid,relationType:b.data.relationType};a.rg.ajax(b.widgetUrl,d,function(){var c=b.get("container");c.hide(b,{},function(){c.remove(!0)}),a.fire("relationDeleted")},b,null,"DELETE")}}})}})},"1.0.0",{requires:["rg-confirm","rg-tooltip"]});
YUI.add("rg.views.publicliterature.PublicationItemFulltextView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationItemFulltextView=a.Base.create("publicliterature.PublicationItemFulltextView",a.rg.WidgetView,[],{events:{".js-open-viewer":{click:"onOpenViewer"},".js-publication-item-fulltext":{mouseenter:"preloadViewer"}},initializer:function(){this.once("rendered",function(){var b=this.get("container"),c=b.one(".js-show-source"),d=b.one(".js-citation-count-tooltip");if(c&&c.plug(a.rg.widget.TooltipPlugin,{content:b.one(".tooltip-content").getContent(),align:"right",arrowOffset:[10,0],overlayOffset:[10,0]}),this.data.previewUrl){var e=a.Node.create('<div class="preview-img"><img src="'+this.data.previewUrl+'" /></div>');e.once("error",function(){e.remove()}),b.one(".js-publication-item-fulltext-content").prepend(e)}d&&d.plug(a.rg.widget.TooltipPlugin,{content:d.getAttribute("data-tooltip")})},this);var b="fulltextRequested:publicationUid-"+this.data.publicationUid,c="fulltextRequestCancelled:publicationUid-"+this.data.publicationUid,d="fulltextRequestFinished:publicationUid-"+this.data.publicationUid;this.events.global||(this.events.global={}),this.events.global[b]="onRequestFulltext",this.events.global[c]="onRequestFulltextCancelled",this.events.global[d]="onRequestFulltextFinished"},preloadViewer:function(){var b=this;!b.preloaded&&b.data.linkId&&b.data.publicationUid&&b.data.previewUrl&&(b.preloaded=!0,a.rg.preloadWidget("publicliterature.PublicLiteratureDocumentViewer.html",this.getViewerParams(),!0))},onOpenViewer:function(b){b.preventDefault();var c=this;c.data.linkId&&c.data.publicationUid&&a.rg.loadWidgetInDialog("publicliterature.PublicLiteratureDocumentViewer.html",this.getViewerParams(),null,this)},getViewerParams:function(){return{publicationId:this.data.publicationUid,reference:this.data.linkId,eventCode:this.data.eventCode,origin:this.data.origin}},onRequestFulltext:function(){var a=this.get("container"),b=a.one(".js-requests-info"),c=this.data.requestCount+1,d=c+" request";1!=c&&(d+="s"),b.setContent(d)},onRequestFulltextCancelled:function(){var a=this.get("container"),b=a.one(".js-requests-info"),c=this.data.requestCount+" request";1!=this.data.requestCount&&(c+="s"),b.setContent(c)},onRequestFulltextFinished:function(){this.data.hasRequested=!0,this.data.requestCount++,this.render({refresh:!0}),this.initializer()}})},"0.0.1",{requires:["rg-header-notify","transition","rg-tooltip"]});
YUI.add("rg-dropdown-plugin",function(a){a.namespace("rg.plugin"),a.rg.plugin.DropdownPlugin=a.Base.create("DropdownPlugin",a.Plugin.Base,[],{activator:null,menu:null,event:null,initializer:function(){var a=this.get("host");this.activator=a.one(this.get("activatorSelector")),this.menu=a.one(this.get("menuSelector")),this.event=this.activator.on("click",this._onToggle,this)},destructor:function(){this.get("host").removeClass(this.get("openClass")),this.event.detach()},_onToggle:function(a){var b=this.get("host"),c=a.target;this.get("ignoreToggle")||c.hasClass("js-ignore-dropdown-toggle")||this.get("ignoreInsideClick")&&c.ancestor(this.get("menuSelector"))&&!c.hasClass(this.get("closeDropdownClass"))||(this.event.detach(),b.hasClass(this.get("openClass"))?this._closeDropdown():this._openDropdown())},_openDropdown:function(){a.Lang.later(10,this,function(){this.event=a.one("document").on("click",this._onToggle,this),this.get("callbackOnOpen")&&this.get("callbackOnOpen").apply(this.get("callbackContext"))});var b=this.get("host"),c=this.get("openClass");b.toggleClass(c)},_closeDropdown:function(){this.event=this.activator.on("click",this._onToggle,this),this.get("callbackOnClose")&&this.get("callbackOnClose").apply(this.get("callbackContext"));var a=this.get("host"),b=this.get("openClass");a.toggleClass(b)}},{NS:"dropdownPlugin",ATTRS:{activatorSelector:{value:".dropdown-toggle"},menuSelector:{value:".dropdown-menu"},openClass:{value:"dropdown-open"},ignoreInsideClick:{value:!1},callbackOnOpen:{value:null},callbackOnClose:{value:null},callbackContext:{value:this},closeDropdownClass:{value:"js-close-dropdown"},ignoreToggle:{value:!1}}})},"0.0.1",{requires:["transition"]});
YUI.add("rg.views.publicliterature.PublicationCitationsView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationCitationsView=a.Base.create("publicliterature.PublicationCitationsView",a.rg.WidgetView,[],{events:{global:{publicationsCitationsUpdated:"publicationsCitationsUpdated","PublicationCitationsList::showMoreLoaded":"publicationCitationsMoreLoaded"},".js-citations":{click:"loadCitations"},".js-cited-in":{click:"loadCitedIn"}},initializer:function(){this.events.global||(this.events.global={});var a="PublicLiteratureDocumentViewerView::download";this.events.global[a]="onDownloadFromDocumentViewer"},afterRendered:function(){var b=this.get("container"),c=b.one(".js-cited-in-tooltip");b.one(".js-citations-sorter")&&this.bindSorting(),c&&c.plug(a.rg.widget.TooltipPlugin,{content:"This list is based on the publications in our database and might not be exhaustive. You can help complete the picture by adding citations."}),this.data.tracking&&this.setupTracking()},bindSorting:function(){var b=this,c=this.get("container"),d=c.one(".js-citations-sorter");d.plug(a.rg.plugin.DropdownPlugin,{}),d.all(".dropdown-menu a").on("click",function(a){b.data.sort=a.currentTarget.getAttribute("data-sort"),c.one(".js-current-sorting").setContent(a.currentTarget.getContent()),b.loadCitations()})},loadCitations:function(a){a&&a.preventDefault();var b=this.get("container");b.one(".js-citations").addClass("tab-item-active"),b.one(".js-cited-in")&&b.one(".js-cited-in").removeClass("tab-item-active"),b.one(".js-citations-sorter").show(),this.data.citationList="outgoing",this._loadList("publicliterature.PublicationCitationsList.html")},loadCitedIn:function(a){a&&a.preventDefault();var b=this.get("container");b.one(".js-citations")&&b.one(".js-citations").removeClass("tab-item-active"),b.one(".js-cited-in").addClass("tab-item-active"),b.one(".js-citations-sorter").hide(),this.data.citationList="incoming",this._loadList("publicliterature.PublicationIncomingCitationsList.html")},_loadList:function(b){var c=this,d=this.get("container").one(".js-citations-list-container"),e={publicationUid:this.data.publicationUid};this.data.sort&&(e.sort=this.data.sort),d.addClass("rendering"),a.rg.loadWidget(b,e,function(a){a.render({replaceContent:d,after:function(){d.removeClass("rendering"),c.data.tracking&&c.setupTracking()}})})},publicationsCitationsUpdated:function(){var b=this,c=this.get("container");c.addClass("rendering"),a.rg.loadWidget(this.widgetUrl,{publicationUid:this.data.publicationUid,sort:this.data.sort,citationList:this.data.citationList},function(a){a.render({replace:c,after:function(){c.removeClass("rendering"),b.data.tracking&&b.setupTracking()}})})},publicationCitationsMoreLoaded:function(){this.data.tracking&&this.setupTracking()},onDownloadFromDocumentViewer:function(){a.fire("PublicationCitationsView::trackInteractionWith",{source:this.data.tracking.sources[".viewer-action-download"],citationList:this.data.citationList,viewer:1})},setupTracking:function(){a.Object.each(this.data.tracking.sources,function(b,c){var d=this.get("container").all(c);if(d){var e=d.get("protocol"),f=e&&0===e.indexOf("http")?"mouseup":"click";d.on(f,function(){a.fire("PublicationCitationsView::trackInteractionWith",{source:b,citationList:this.data.citationList})},this)}},this)}})},"1.0.0",{requires:["rg-dropdown-plugin","rg-tooltip"]});
YUI.add("rg.views.publicliterature.PublicationIncomingCitationsListView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationIncomingCitationsListView=a.Base.create("publicliterature.PublicationIncomingCitationsListView",a.rg.WidgetView,[],{events:{".js-add-citation-from-own-publication":{click:"addIncomingCitationFromOwnPublication"},".js-add-citation-request-publication":{click:"requestIncomingCitation"},".js-show-more":{click:"showMore"}},addIncomingCitationFromOwnPublication:function(){a.rg.loadWidgetInDialog("literature.AddCitedByOwnPublicationDialog.html",{publicationUid:this.data.publicationUid})},requestIncomingCitation:function(){a.rg.loadWidgetInDialog("literature.AddCitationRequestPublicationDialog.html",{publicationUid:this.data.publicationUid})},showMore:function(b){b&&b.preventDefault();var c={publicationUid:this.data.publicationUid,sort:this.data.sort,limit:this.data.pageSize,offset:this.data.newOffset},d=this.get("container").one(".c-list");this.get("container").one(".js-show-more").hide(),this.get("container").one(".list-loading").show(),a.rg.loadWidget(this.widgetUrl,c,function(b){var c=b.data.citationItems;this.data.pageSize=b.data.pageSize,this.data.newOffset=b.data.newOffset,this.data.hasShowMore=b.data.hasShowMore,a.Array.each(c,function(b){try{a.rg.createWidget(b,function(a){a.render({append:d})})}catch(c){a.log(c)}},this),this.data.hasShowMore&&this.get("container").one(".js-show-more").show(),this.get("container").one(".list-loading").hide()},this)}})},"1.0.0",{requires:[]});
YUI.add("rg.views.publicliterature.PublicationItemView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationItemView=a.Base.create("publicliterature.PublicationItemView",a.rg.WidgetView,[],{events:{".js-toggle-abstract":{click:"collapse"},".action-remove":{click:"remove"},".action-follow":{click:"toggleFollow"},".action-download":{click:"download"},".action-request.primary":{click:"request"},".action-request.image":{click:"request"},".action-departmentremove":{click:"removeFromDepartmentpage"},".action-profileremove":{click:"removeFromProfile"},".action-remove-citation":{click:"removeCitationPublication"},".action-share":{click:"sharePublication"}},publicationBookmarkEndpoint:"literature.AjaxFollowPublication.html",publicationAuthorshipEndpoint:"literature.AjaxPublicationAuthorship.html",initializer:function(){var a="fulltextPreviewClosed:publicationUid-"+this.data.publicationUid;this.events.global||(this.events.global={}),this.events.global[a]="onPreviewClosed"},afterRendered:function(){var b=this.get("container");b.plug(a.rg.plugins.ContainerHover,{cssClasses:"list-hover"});var c=b.one(".js-pending");c&&c.plug(a.rg.widget.TooltipPlugin,{content:b.one(".info-tooltip-content").getContent(),align:"right",arrowOffset:[10,0],overlayOffset:[10,0]});var d={};this.data.displayUpdatedExpanderPlugin&&(d.expandLinkText="+ more",d.collapseLinkText="- less"),this.data.collapseTitle&&b.one(".js-title")&&b.one(".js-title").plug(a.rg.plugins.Expander,d),this.data.collapseAuthors&&b.one(".js-authors")&&b.one(".js-authors").plug(a.rg.plugins.Expander,d),this.data.collapseAbstract&&b.one(".js-abstract")&&b.one(".js-abstract").plug(a.rg.plugins.Expander,d),this.hasSeenPromo=!1,this.hasRequested=!1},download:function(){this.data.showPublicationDownloadDataUsagePermissionDialog&&a.Lang.later(2e3,this,function(){a.rg.loadWidget("literature.PublicationDownloadDataUsagePermissionDialog.html",{},function(b){b.getDefaultDialogConfig=function(){return{hideOnClickOutside:!1,plugins:[{fn:a.Plugin.OverlayAutohide,cfg:{clickedOutside:!1,pressedEscape:!0,focusedOutside:!1}}]}};try{b.render({dialog:!0})}catch(c){return!1}})},this)},removeCitationPublication:function(){this.data.publicationCitationUid&&this.data.citationSourcePublicationUid?this.removeOutgoingCitationPublication():this.removeIncomingCitationPublication()},removeOutgoingCitationPublication:function(b){b&&b.preventDefault();var c=this;a.rg.confirm({header:"Remove Citation",body:"Are you sure you want to remove this citation?",buttons:[{id:"confirm",label:"Remove"},{id:"cancel",label:"Cancel"}],callback:function(b){"confirm"===b&&a.rg.ajaxDbwAware("publicliterature.PublicationCitationsList.removeCitation.html",{publicationUid:c.data.citationSourcePublicationUid,publicationCitationUid:c.data.publicationCitationUid},function(b){b.success?(a.Lang.isArray(b.result)&&1===b.result.length&&a.rg.notify(b.result[0],"attention"),this.get("container").destroy(!0)):a.Lang.isArray(b.errors)&&1===b.errors.length?a.rg.notify(b.errors[0],"warning"):a.rg.notify("An error occurred.","warning")},c,{},"POST")}})},removeIncomingCitationPublication:function(b){b&&b.preventDefault();var c=this;a.rg.confirm({header:"Remove Citation",body:"Are you sure you want to remove this citation?",buttons:[{id:"confirm",label:"Remove"},{id:"cancel",label:"Cancel"}],callback:function(b){"confirm"===b&&a.rg.ajaxDbwAware("publicliterature.PublicationIncomingCitationsList.removeCitation.html",{citingPublicationUid:c.data.publicationUid,citedPublicationUid:c.data.citationSourcePublicationUid},function(b){b.success?(a.Lang.isArray(b.result)&&1===b.result.length&&a.rg.notify(b.result[0],"attention"),this.get("container").destroy(!0)):a.Lang.isArray(b.errors)&&1===b.errors.length?a.rg.notify(b.errors[0],"warning"):a.rg.notify("An error occurred.","warning")},c,{},"POST")}})},collapse:function(a){a.preventDefault();var b=this.get("container"),c=b.one(".abstract");c.toggleClass("collapsed")},_baseRemoveDialog:function(b,c,d){b.preventDefault();var e=this;a.rg.loadWidget("literature.PublicationRemoveDialog.html",{publicationUid:this.data.publicationUid,contextSource:c},function(a){a.on("publicationRemove",d,e),a.render({dialog:{}})})},remove:function(a){this._baseRemoveDialog(a,"profile",this.removePublication)},removeFromDepartmentpage:function(a){this._baseRemoveDialog(a,"department",this.removePublication)},removeFromProfile:function(a){this.showRgDoiPublicationDeletionRequestDialog()?this.openRgDoiPublicationDeletionRequestDialog():this._baseRemoveDialog(a,"profile",this.removePublication)},removePublication:function(b){var c={publicationUid:this.data.publicationUid,reason:b.remove_option,reasonText:b.remove_text,contextSource:this.data.context,contextId:this.data.contextId},d=this.get("container");a.rg.ajaxDbwAware(this.publicationAuthorshipEndpoint,c,function(b){b.success&&a.rg.notify(b.result[0],"promo")},this,null,"DELETE"),d.hide("fadeOut",{},function(){d.destroy(!0)})},sharePublication:function(b){b.preventDefault(),a.rg.loadWidgetInDialog("literature.PublicationShareDialog.html",{publicationUid:this.data.publicationUid})},toggleFollow:function(b){b.preventDefault();var c={publicationUid:this.data.publicationUid,context:this.get("followContext")};b.currentTarget.setContent(this.data.isReader?"Follow":"Following"),b.currentTarget.toggleClass("active"),!this.data.isReader&&this.data.eventCode&&(c.eventCode=this.data.eventCode),a.rg.ajaxDbwAware(this.publicationBookmarkEndpoint,c,function(b){b.success&&a.rg.notify(b.result[0],"promo")},this,null,this.data.isReader?"DELETE":"POST"),this.data.isReader=!this.data.isReader},onPreviewClosed:function(){this.openFulltextRequestInvitationDialog()},request:function(b){if(b&&b.preventDefault(),!b.currentTarget.hasClass("disabled")){var c=this,d=this.get("container"),e="pubitem";this.data.eventCode&&(e+="-"+this.data.eventCode),this.disableAllActions(d),a.rg.ajax(this.data.requestEndpoint,{resourceId:this.data.publicationUid,context:e},function(e){e.success?e.result.requested?(c.hasRequested=!0,a.rg.notify("Full-text requested.","attention"),c.enableUndo(d),a.fire("fulltextRequested:publicationUid-"+c.data.publicationUid),b.currentTarget.hasClass("image")&&c.get("opensViewer")||c.openFulltextRequestInvitationDialog(),c.undoTimeout=a.later(1e4,c,c.disableFurtherRequest,[d])):e.result.requestCancelled&&(c.hasRequested=!1,a.rg.notify("Full-text request cancelled.","attention"),c.undoTimeout&&c.undoTimeout.cancel(),c.resetButtons(d),a.fire("fulltextRequestCancelled:publicationUid-"+c.data.publicationUid)):(a.rg.notify(e.errors,"warning"),c.resetButtons(d))})}},disableAllActions:function(a){var b=a.one(".js-request-btn"),c=a.one(".action-request.image");c&&c.addClass("disabled"),b&&b.addClass("disabled")},resetButtons:function(a){var b=a.one(".js-request-btn"),c=a.one(".action-request.undo"),d=a.one(".publication-preview"),e="";d&&(d.removeClass("disabled"),e=d.one(".preview-action"),e.one(".text-request").removeClass("hidden"),e.one(".text-requested").addClass("hidden")),b.removeClass("hidden"),b.removeClass("disabled"),c.addClass("hidden"),c.addClass("btn-disabled")},enableUndo:function(a){var b=a.one(".js-request-btn"),c=a.one(".action-request.undo"),d=a.one(".publication-preview"),e="";d&&(d.addClass("preview-undo"),e=d.one(".preview-action"),e.one(".text-request").addClass("hidden"),e.one(".text-requested").removeClass("hidden")),c.removeClass("hidden"),c.removeClass("btn-disabled"),b.addClass("hidden")},disableFurtherRequest:function(b){var c=b.one(".action-request.undo"),d=b.one(".js-request-btn");d.addClass("btn-disabled"),c.addClass("btn-disabled"),c.removeClass("undo"),c.addClass("requested"),a.fire("fulltextRequestFinished:publicationUid-"+this.data.publicationUid)},openFulltextRequestInvitationDialog:function(){!this.hasSeenPromo&&this.hasRequested&&(a.rg.loadWidget(this.get("requestFulltextInvitationDialogUrl"),{publicationUid:this.data.publicationUid},function(b){try{b.render({dialog:!0})}catch(c){a.log("Could not load widget.")}},this),this.hasSeenPromo=!0)},showRgDoiPublicationDeletionRequestDialog:function(){return this.get("isRgDoi")&&this.get("canDeletePublication")},openRgDoiPublicationDeletionRequestDialog:function(){var b=this;a.rg.loadWidgetInDialog(this.get("rgDoiPublicationDeletionRequestDialog"),{},function(){this.dialog.on("publicationRemove",b.removePublication,b)})}},{ATTRS:{requestEndpoint:{value:""},opensViewer:{value:!1},requestFulltextInvitationDialogUrl:{},isRgDoi:{value:!1},canDeletePublication:{value:!1},followContext:{},rgDoiPublicationDeletionRequestDialog:{value:!1}}})},"0.0.1",{requires:["rg-header-notify","transition","rg-confirm","rg-container-hover","rg-tooltip","rg-expander"]});
YUI.add("rg.core.form.RgChosen",function(a){a.namespace("rg.core.form"),a.rg.core.form.RgChosen=function(b,c){if(a.UA.ie>0&&a.UA.ie<9)return!1;var d=a.one(b);return d?new Chosen(d.getDOMNode(),c):!1}},"1.0.0",{requires:["chosen"]});
YUI.add("rg-sticky-header-plugin",function(a){a.namespace("rg.header"),function(){a.rg.header.StickyHeaderPlugin=a.Base.create("StickyHeaderPlugin",a.Plugin.Base,[],{initializer:function(){var b=a.Node.create("<div></div>"),c=a.Node.create("<div></div>");this.body=a.one("win"),this.node=this.get("host"),this.isFixed=0,this.fixedClass="fixed-scrolling",this.placeholder=b,this.nodeTopDummy=c.setStyles({height:0}),this.get("restrictToContainer")&&(this.restrictToContainerTop=this.get("restrictToContainer").getY()),this.placeholder.addClass("sticky-placeholder"),this.recalculateLayout(),this.node.insert(c,"before"),this.node.insert(b,"before"),this.node.appendTo(b),this.handlers=[],this.handlers.push(a.one("window").on("scroll",this._handleScroll,this)),this._handleScroll()},_handleScroll:function(){var a=this.body.get("scrollTop");if(a>=this.nodeTop&&!this.isFixed?(this.isFixed=1,this.node.addClass(this.fixedClass)):a<=this.nodeTop&&this.isFixed&&(this.isFixed=0,this.node.removeClass(this.fixedClass)),this.isFixed&&this.get("restrictToContainer")){var b=this.restrictToContainerTop+this.get("restrictToContainer").get("offsetHeight"),c=this.node.get("offsetHeight")+this.body.get("scrollTop");c>b?this.node.setStyle("top",b-c):this.node.setStyle("top",0)}},recalculateLayout:function(){this.nodeTop=this.node&&this.node.getY()+this.get("stickyOffsetTop"),this.placeholder.setStyle("height",this.get("host").get("offsetHeight"))},updateNodeTop:function(){this.nodeTop=this.nodeTopDummy.getY()+this.get("stickyOffsetTop")},destructor:function(){a.Array.each(this.handlers,function(a){a.detach()})}},{NS:"StickyHeaderPlugin",ATTRS:{stickyOffsetTop:{value:0},restrictToContainer:{value:null}}})}()},"0.0.1",{requires:[]});
YUI.add("rg.views.publicliterature.PublicationInlineReaderView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationInlineReaderView=a.Base.create("publicliterature.PublicationInlineReaderView",a.rg.WidgetView,[],{events:{".js-publication-version-select":{change:"changeVersion"},".js-open-large-pdf":{click:"lazyLoadViewer"}},destructor:function(){this.messageHandler&&this.messageHandler.detach()},afterRendered:function(){var b=this,c=this.get("container"),d=c.one(".js-sticky-header");d.plug(a.rg.header.StickyHeaderPlugin,{}),this.trackedDownloads={},a.rg.core.form.RgChosen(".js-publication-version-select",{disable_search:!0}),this.messageHandler=a.on("pdf-js-download",function(a){b.trackDownload(a.type)})},changeVersion:function(){var b=this.get("container"),c=b.one(".js-publication-version-select option:checked"),d=b.one(".js-doi-container"),e=d.one(".js-doi"),f=b.one(".file-size-note-container"),g=b.one(".js-name");c.get("value")&&(c.getAttribute("data-doi")?(d.setStyle("display","inline-block"),e.set("text",c.getAttribute("data-doi"))):d.setStyle("display","none"),g.set("text",c.getAttribute("data-name")),g.set("href",c.getAttribute("data-name-link")),b.one(".js-publication-date")&&b.one(".js-publication-date").set("text",c.getAttribute("data-date")),a.fire("pdf-js-version-change",{url:c.get("value")}),a.rg.loadWidget(this.data.reader.widgetUrl.split("?")[0]+"?fileHref="+c.get("value"),{},function(a){a.render({replaceContent:f})}))},lazyLoadViewer:function(b){var c=new a.rg.core.layout.ResponsiveHelpers;if(!c.matchesBreakpoint("s-lt")){b.preventDefault();var d=this.get("container").one(".file-size-note-container");a.rg.loadWidget(this.data.reader.widgetUrl,{},function(a){a.render({replaceContent:d})})}},trackDownload:function(b){var c=this._getDisplayedPublication(),d="v";switch(b){case"pagechange":d="v";break;case"download":d="d"}var e=this.data.trackedDownloads[c.linkId][d];e||(this.data.trackedDownloads[c.linkId][d]=!0,a.rg.ajax(this.data.downloadTrackUrl,{type:b,linkId:c.linkId,pubId:this.data.publicationUid},function(a){a.success||(this.data.trackedDownloads[c.linkId][d]=!1)},this,null,"GET"))},_getDisplayedPublication:function(){var a=this.get("container"),b=a.one(".js-publication-version-select option:checked"),c=null;if(b&&(c=b.getData("link-id")),c){var d=this.data.displayableLinks.filter(function(a){return a.linkId==c});return d[0]?d[0]:this.data.defaultLinkData}return this.data.defaultLinkData}})},"1.0.0",{requires:["rg.core.form.RgChosen","rg.core.layout.ResponsiveHelpers","rg-sticky-header-plugin"]});
YUI.add("rg.views.publicliterature.PublicationActionCountView",function(a){a.namespace("rg.views.publicliterature"),a.rg.views.publicliterature.PublicationActionCountView=a.Base.create("publicliterature.PublicationActionCountView",a.rg.WidgetView,[],{events:{global:{updateCounts:"updateCounts"}},updateCounts:function(){var b=this.get("container");a.rg.loadWidget(this.widgetUrl,{publicationUid:this.data.publicationUid},function(a){a.render({replace:b})},this)}})},"0.0.1",{requires:["rg-header-notify","transition"]});