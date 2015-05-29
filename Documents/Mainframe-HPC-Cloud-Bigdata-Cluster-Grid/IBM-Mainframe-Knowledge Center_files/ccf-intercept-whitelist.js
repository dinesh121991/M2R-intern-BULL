try {
	ibmweb.dynnav.ccfintercept.callback_whitelist([
		"http://w3dev\\.somerslab\\.ibm\\.com/branches/ol-v17-test/ol-test/intercept/www/percent-100-whitelisted\\.html",
		
		
		/* 	
		 * 	IBM Analytics & Big Data Application, 
		 * 	For intercept survey percentage Exception
		 */
		{
			"for": "percentage",
			"type": "URL",
			"limit": "75",
			"value": [
		          	
		          	/* IBM Analytics URL's*/
		    		"https*://www.ibm.com/analytics/us/en/descriptive-analytics/index.html",
		    		"https*://www.ibm.com/analytics/us/en/diagnostic-analytics/index.html",
		    		"https*://www.ibm.com/analytics/us/en/predictive-analytics/index.html",
		    		"https*://www.ibm.com/analytics/us/en/prescriptive-analytics/index.html",
		    		"https*://www.ibm.com/analytics/us/en/index.html",
		    		"https*://www.ibm.com/analytics/us/en/outperform-the-competition.html",
		    		"https*://www.ibm.com/analytics/us/en/analytics-technology/index.html",
		    		"https*://www.ibm.com/analytics/us/en/conversations/index.html",
		    		
		    		/* IBM Big Data URL's */
		    		"https*://www.ibm.com/big-data/us/en/index.html",
		    		"https*://www.ibm.com/big-data/us/en/technology/index.html",
		    		"https*://www.ibm.com/big-data/us/en/conversations/index.html"		          	
			]			
		},
		
		/* CustomB Exception
		 * ---------------------------------------------------------------------------------------
		 * Developers can add any custom embedded form to intercept survey, custom URL's requires exception
		 * Intercept Custom Exception URL's   
		 */
		{
			"for": "customB",
			"type": "URL",
			"value": [
			          
			        /* Intercept custom exception given by Ben, for testing */
			        "http://tealeaf03.atl.dst.ibm.com/standards/UE_MT/eSlpSurvey/eSlpSurvey-standalone.html",
			        
			        /* Intercept custom exception for KnowledgeCenetr(KC) */
			        "http://r9x0ea9.ibm.com:9080/support/knowledgecenter/exitsurvey/survey.html",
			        "http://www-01.ibm.com/support/knowledgecenter/exitsurvey/survey.html"
			]			
		},
		
		/* 	Intercept Percentage Exception Testing URL's */
		{
			"for": "percentage",
			"type": "URL",
			"limit": "90",
			"value": [
			        "https*://webdev\.webmaster\.ibm\.com/common/testpages/misc_stuff/opinionlab/.*",
			        "http://localhost/common/testpages/jay_issues/intercept/.*",
			        "https*://webdev\.webmaster\.ibm\.com/common/testpages/jay_issues/intercept/.*"
			]			
		}
		

	]);
} catch (ev) {
	if (typeof(console) != "undefined")
		console.warn("CCF whitelist completed, but the callback was not defined.");
}