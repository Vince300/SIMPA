package drivers.efsm.real;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;
import java.util.logging.Level;

import javax.swing.JOptionPane;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.commons.logging.LogFactory;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import tools.HTTPData;
import tools.Utils;
import tools.loggers.LogManager;
import automata.efsm.Parameter;
import automata.efsm.ParameterizedInput;
import automata.efsm.ParameterizedOutput;

import com.gargoylesoftware.htmlunit.CookieManager;
import com.gargoylesoftware.htmlunit.HttpMethod;
import com.gargoylesoftware.htmlunit.WebClient;
import com.gargoylesoftware.htmlunit.WebRequest;
import com.gargoylesoftware.htmlunit.html.HtmlPage;
import com.gargoylesoftware.htmlunit.util.Cookie;

import crawler.Configuration;
import crawler.DriverGenerator;
import crawler.WebInput;
import crawler.WebInput.Type;
import crawler.WebOutput;
import java.util.Iterator;
import java.util.Map;
import org.apache.http.conn.HttpHostConnectException;
import org.w3c.dom.Node;

public class GenericDriver extends LowWebDriver {

	protected WebClient client = null;
	public static Configuration config = null;
	private final List<WebInput> inputs;
	private final List<WebOutput> outputs;
	private Map<WebInput, String> inputSymbols; 
	private Map<WebOutput, String> outputSymbols;
	private Map<String, WebInput> inputsFromSymbols;

	private final String NO_PARAM_NAME = "noparam";
	private final String NO_PARAM_VALUE = Parameter.PARAMETER_NO_VALUE;
	
	@SuppressWarnings("deprecation")
	public GenericDriver(String xml) throws IOException {
		inputs = new ArrayList<>();
		outputs = new ArrayList<>();
		config = LoadConfig(xml);
		generateSymbols();
		LogFactory.getFactory().setAttribute("org.apache.commons.logging.Log", "org.apache.commons.logging.impl.NoOpLog");
	    java.util.logging.Logger.getLogger("com.gargoylesoftware.htmlunit").setLevel(Level.OFF); 
	    java.util.logging.Logger.getLogger("org.apache.commons.httpclient").setLevel(Level.OFF);
		client = new WebClient();
		client.getOptions().setThrowExceptionOnFailingStatusCode(false);
		client.getOptions().setTimeout(10000);
		client.getOptions().setUseInsecureSSL(true);
		CookieManager cm = new CookieManager();
		if (config.getCookies() != null){
			String cookieValue = null;
			while (cookieValue == null){
				cookieValue = (String)JOptionPane.showInputDialog(null, "Cookies value required :",
							"Loading test driver ...",
							JOptionPane.PLAIN_MESSAGE,
							null,
							null,
							config.getCookies());
			}
			for (String cookie : cookieValue.split("[; ]")) {
				String[] cookieValues = cookie.split("=");
				cm.addCookie(new Cookie(config.getHost(), cookieValues[0],
						cookieValues[1]));
			}			
		}
		client.setCookieManager(cm);
		BasicCredentialsProvider creds = new BasicCredentialsProvider();
		if (config.getBasicAuthUser() != null
				&& config.getBasicAuthPass() != null) {
			creds.setCredentials(
					new AuthScope(config.getHost(), config.getPort()),
					new UsernamePasswordCredentials(config.getBasicAuthUser(),
							config.getBasicAuthPass()));
		}
		client.setCredentialsProvider(creds);
		client.getOptions().setJavaScriptEnabled(false);
		client.getOptions().setCssEnabled(false);
	}

	@Override
	public String getSystemName() {
		return config.getName();
	}

	/**
	 * Send an abstract input to the web aplication and return an abstraction of its response.
	 * @param pi the input to send
	 * @return the response of the web application
	 */
	@Override
	public ParameterizedOutput execute(ParameterizedInput pi) {
		numberOfAtomicRequest++;

		/* Sends the parameterized input to the server and retrieve the HTML source code of the response */
		String source = submit(pi);

		/* Translate the response in an parameterized output symbol */ 
		ParameterizedOutput po = htmlToParameterizedOutput(source);
		
		LogManager.logRequest(pi, po);
		return po;
	}

	/**
	 * Translate a HTML source code into a parameterized symbol.
	 * 
	 * @param htmlPage
	 * @return 
	 */
	public ParameterizedOutput htmlToParameterizedOutput(String htmlPage){
		ParameterizedOutput po = null;
		//Creates the WebOutput object from html source
		WebOutput out = new WebOutput(htmlPage, config.getLimitSelector()); //TODO add 'from' ?
		//Looks for a equivalent output from the already visited ones
		boolean equivalentOutputFound = false;
		for (int i = 0; i < outputs.size(); i++) {
			if (out.isEquivalentTo(outputs.get(i))) {
				if (equivalentOutputFound) {
					throw new InternalError("The current output has more than "
							+ "one equivalent : this should not happen");
				} else {
					equivalentOutputFound = true;
				}
				po = new ParameterizedOutput(getOutputSymbols().get(i));
				//If equivalent output has no output parameters...
				if (outputs.get(i).getParamsNumber() == 0) {
					//...create a default one for po
					po.getParameters().add(new Parameter());
				} else {
					//...else, adds to po every parameter stored in the output
					for (Iterator<String> iter = outputs.get(i).getParamsIterator() ; iter.hasNext();) {
						String p = iter.next();
								po.getParameters().add(
								new Parameter(out.extractParam(p)));
					}
				}
			}
		}

		//If a new page is discovered during the inference
		if (po == null) {
			//System.err.println("Different page found");
			po = new ParameterizedOutput();
		}
		return po;
	}

	/**
	 * Create the Data section of a HTTP request corresponding to the given input sympol.
	 * @param in the WebInput structure that holds the parameters names
	 * @param pi the ParameterizedInput that contains the parameters values
	 * @return a HTTPData object that contains the Data section of the request
	 */
	private HTTPData getRequestData(WebInput in, ParameterizedInput pi) {
		HTTPData data = new HTTPData();
		TreeMap<String, List<String>> params = in.getParams();
		int i = 0;
		for (String key : params.keySet()) {
			data.add(key, pi.getParameterValue(i++));
		}
		return data;
	}

	/**
	 * Create the URL containing HTTP parameters corresponding to the given input symbol
	 * @param in the WebInput structure that holds the parameters names
	 * @param pi the ParameterizedInput that contains the parameters values
	 * @return the complete URL corresponding to the input
	 */
	public String getAddressWithParameters(WebInput in, ParameterizedInput pi) {
		if (in.getMethod() != HttpMethod.GET) {
			throw new IllegalArgumentException("Internal error : this method should "
					+ "not be called for an input with a method other than GET");
		}
		String addr = in.getAddress() + "?";
		TreeMap<String, List<String>> params = in.getParams();
		int i = 0;
		for (String key : params.keySet()) {
			addr += key + "=" + pi.getParameterValue(i++) + "&";
		}

		addr = addr.substring(0, addr.length() - 1);
		return addr;
	}

	/**
	 * @see GenericDriver#submit(automata.efsm.ParameterizedInput, boolean) 
	 */
	public String submit(ParameterizedInput pi) {
		return submit(pi, false);
	}


	/**
	 * Convert a parameterized input into a concrete request and send it to the server
	 * @param pi the abstract input
	 * @param rawResponse if true, returns the raw HTTP response instead of parsing it
	 * @return The HTML source code of the response
	 */
	public String submit(ParameterizedInput pi, boolean rawResponse) {
		WebRequest request = null;
		try {
			request = parameterizedInputToRequest(pi);
			HtmlPage page;
			page = client.getPage(request);
			if (rawResponse) {
				return page.getWebResponse().getContentAsString();
			} else {
				return page.asXml();
			}
		} catch (Exception e) {
			System.err.println("Incriminated input : " + request.toString());
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * Convert a parameterized input into a concrete request
	 * @param pi
	 * @return 
	 */
	public WebRequest parameterizedInputToRequest(ParameterizedInput pi) {
		try {
			WebInput in = inputsFromSymbols.get(pi.getInputSymbol());
			HttpMethod method = in.getMethod();
			WebRequest request = null;
			request = new WebRequest(new URL(in.getAddress()), in.getMethod());
			
			if (in.getParams().containsKey(NO_PARAM_NAME)){
				pi = pi.clone();
				pi.getParameters().remove(0);
				in = (WebInput) in.clone();
				in.getParams().remove(NO_PARAM_NAME);
			}
			switch (method) {
				case POST:
					HTTPData values = getRequestData(in, pi);
					request.setRequestParameters(values.getNameValueData());
					request.setAdditionalHeader("Connection", "Close");
					break;
				case GET:
					request.setUrl(new URL(getAddressWithParameters(in, pi)));
					break;
				default:
					throw new UnsupportedOperationException(method + " method not supported yet.");
			}

			return request;
		} catch (MalformedURLException | CloneNotSupportedException ex) {
			LogManager.logException("Internal error : this should not happen", ex);
			throw new AssertionError("Internal error : this should not happen");
		}
	}
	

	@Override
	public void reset(){
		super.reset();
		if (config.getCookies() == null) {
			client.getCookieManager().clearCookies();
		}
		if (config.getReset() != null && !config.getReset().isEmpty()) {
			try {
				client.getPage(config.getReset());
			} catch (HttpHostConnectException e) {
				LogManager.logFatalError("Unable to connect to host");
			} catch (Exception e) {
				LogManager.logException("Error resetting application", e);
			}
		}
	}
	
	/**
	 * Read the XML configuration file generated by the crawler
	 * @see DriverGenerator
	 * @param xml the content of the file
	 * @return an object containing the settings
	 * @throws IOException 
	 */
	private Configuration LoadConfig(String xml) throws IOException {
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		config = new Configuration();
		try {
			DocumentBuilder db = dbf.newDocumentBuilder();
			db.setErrorHandler(null);
			org.w3c.dom.Document dom = db.parse(xml);
			Element root = dom.getDocumentElement();
			config.setName(root.getElementsByTagName("target").item(0)
					.getTextContent());
			config.setHost(root.getElementsByTagName("host").item(0)
					.getTextContent());
			config.setPort(Integer.parseInt(root.getElementsByTagName("port")
					.item(0).getTextContent()));
			config.setReset(root.getElementsByTagName("reset").item(0)
				.getTextContent());
			config.setBasicAuthUser(root.getElementsByTagName("basicAuthUser")
					.item(0).getTextContent());
			config.setBasicAuthPass(root.getElementsByTagName("basicAuthPass")
					.item(0).getTextContent());
			config.setLimitSelector(root.getElementsByTagName("limitSelector")
					.item(0).getTextContent());
			config.setCookies(root.getElementsByTagName("cookies").item(0)
					.getTextContent());

			Node inputsNode = root.getElementsByTagName("inputs").item(0);
			NodeList inputNodesList = inputsNode.getChildNodes();
			for (int i = 0; i < inputNodesList.getLength(); i++) {
				if (!inputNodesList.item(i).getNodeName().equals("input")) {
					continue;
				}

				Node inputNode = inputNodesList.item(i);
				WebInput in = new WebInput();
				in.setAddress(inputNode.getAttributes()
					.getNamedItem("address").getNodeValue());
				in.setMethod(HttpMethod.valueOf(inputNode
					.getAttributes().getNamedItem("method")
					.getNodeValue()));
				in.setType(Type.valueOf(inputNode.getAttributes()
					.getNamedItem("type").getNodeValue()));

				int nbValue = 0;
				if (!inputNode.getChildNodes().item(1).getNodeName().equals("parameters")) {
					continue;
				}

				Node parametersNode = inputNode.getChildNodes().item(1);
				NodeList parametersCombinationNodesList = parametersNode.getChildNodes();
				for (int j = 0; j < parametersCombinationNodesList.getLength(); j++) {
					if (!parametersCombinationNodesList.item(j).getNodeName().equals("parametersCombination")) {
						continue;
					}
					Node parametersCombinationNode = parametersCombinationNodesList.item(j);
					nbValue++;

					for (int k = 0; k < parametersCombinationNode.getChildNodes().getLength(); k++) {
						if (!parametersCombinationNode.getChildNodes().item(k).getNodeName().equals("parameter")) {
							continue;
						}

						Node parameterNode = parametersCombinationNode.getChildNodes().item(k);
						String name = parameterNode.getAttributes().getNamedItem("name").getNodeValue();
						String value = parameterNode.getTextContent();
						if (in.getParams().get(name) == null) {
							in.getParams().put(name,
								new ArrayList<String>());
						}
						in.getParams().get(name).add(value);
					}
				}
				in.setNbValues(nbValue);
				if (in.getParams().isEmpty()) {
					in.getParams().put(NO_PARAM_NAME,
						Utils.createArrayList(NO_PARAM_VALUE));
					in.setNbValues(1);
				}
				this.inputs.add(in);
			}

			NodeList outputNodesList = root.getElementsByTagName("outputs").item(0)
				.getChildNodes();
			for (int i = 0; i < outputNodesList.getLength(); i++) {
				Node outputNode = outputNodesList.item(i);
				if (!outputNode.getNodeName().equals("output")) {
					continue;
				}
				String source = outputNode.getChildNodes().item(1).getTextContent();
				WebOutput out = new WebOutput(source);
				NodeList parameterNodesList = outputNode.getChildNodes().item(3).getChildNodes();
				for (int j = 0; j < parameterNodesList.getLength(); j++) {
					if (!parameterNodesList.item(j).getNodeName().equals("parameter")) {
						continue;
					}
					String value = parameterNodesList.item(j).getTextContent();
					out.addParam(value);
				}
				this.outputs.add(out);

			}
		} catch (ParserConfigurationException | SAXException e) {
			LogManager.logException("Error parsing the xml file \"" + xml + "\"", e);
		} catch (IOException e) {
			LogManager.logException("Unable to read the file \"" + xml + "\"", e);
		}
		return config;
	}

	@Override
	public HashMap<String, List<ArrayList<Parameter>>> getDefaultParamValues() {
		HashMap<String, List<ArrayList<Parameter>>> defaultParamValues = new HashMap<>();
		ArrayList<ArrayList<Parameter>> params = null;
		ArrayList<Parameter> one = null;
		int index = 0;
		for (WebInput i : inputs) {
			params = new ArrayList<>();
			int nbParam = i.getNbValues();
			for (int k = 0; k < nbParam; k++) {
				one = new ArrayList<>();
				for (String key : i.getParams().keySet()) {
					one.add(new Parameter(i.getParams().get(key).get(k)));
				}
				params.add(one);
			}
			defaultParamValues.put(getInputSymbol(i), params);
			index++;
		}
		return defaultParamValues;
	}

	@Override
	public TreeMap<String, List<String>> getParameterNames() {
		TreeMap<String, List<String>> res = new TreeMap<>();
		for (WebInput i : inputs) {
			List<String> names = new ArrayList<>();
			for (String key : i.getParams().keySet()) {
				names.add(key);
			}
			res.put(getInputSymbol(i), names);
		}
		for (WebOutput o : outputs) {
			String outputSymbol = getOutputSymbol(o);
			List<String> names = new ArrayList<>();
			if (o.getParamsNumber() == 0) {
				names.add(outputSymbol + "_status");
			} else {
				for (int n = 0; n < o.getParamsNumber(); n++) {
					names.add(outputSymbol + "_param"
							+ String.valueOf(n));
				}
			}
			res.put(outputSymbol, names);
		}
		return res;
	}

	@Override
	public List<String> getInputSymbols() {
		return new ArrayList(inputSymbols.values());
	}

	@Override
	public List<String> getOutputSymbols() {
		List<String> os = new ArrayList<>();
		for (int i = 0; i < outputs.size(); i++) {
			os.add("output_" + i);
		}
		return os;
	}

	private void generateSymbols() {
		inputSymbols = new HashMap<>();
		for (WebInput i : inputs) {
			String[] splitedAddress = i.getAddress().split("/");
			String pageName = splitedAddress[splitedAddress.length - 1];
			//To be compatible with ASLan++
			pageName = pageName.replaceAll("[^a-zA-Z_0-9]", "_");
			if (inputSymbols.containsValue(pageName)) {
				int counter = 2;
				while (inputSymbols.containsValue(pageName + "_" + counter)) {
					counter++;
				}
				inputSymbols.put(i, pageName + "_" + counter);
			} else {
				inputSymbols.put(i, pageName);
			}
		}
		
		outputSymbols = new HashMap<>();
		int i = 0;
		for (WebOutput o : outputs) {
			outputSymbols.put(o, "output_" + i);
			i++;
		}
		
		
		inputsFromSymbols = new HashMap<>();
		for (Map.Entry<WebInput, String> entry : inputSymbols.entrySet()) {
			WebInput key = entry.getKey();
			String value = entry.getValue();
			if (inputsFromSymbols.put(value, key) != null) {
				throw new AssertionError("The symbol " + value + " should be unique");
			}
		}
	}
	
	private String getOutputSymbol(WebOutput o) {
		return outputSymbols.get(o);
	}

	private String getInputSymbol(WebInput i) {
		String symbol = inputSymbols.get(i);
		if (symbol == null) {
			throw new AssertionError("An input symbol is missing");
		}
		return symbol;
	}
}
