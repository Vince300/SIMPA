package simpa.hit.crawler.page;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.jsoup.nodes.Document;
import org.jsoup.nodes.Node;

public class PageTreeNode extends GenericTreeNode<String> {

	/**
	 * TODO : maintain a whitelist instead of a blacklist (with div, h1, h2, h3, h4, form, input, ...
	 */
	public static Set<String> excludedNode = new HashSet<String>(Arrays.asList(new String[] {
			"#document", "#text", "span", "font", "a", "center", "bold", "italic", "style", "base", "param", "script", "noscript",
			"b", "i", "tt", "sub", "meta", "title", "head", "tbody", "sup", "big", "small", "img", "br", "tr", "td", "option", "#comment", "#data", "strong"
			,"p", "ul", "li", "link"
			}));

	public PageTreeNode(String nodeName){
		super(nodeName);
	}
	
	public PageTreeNode(Document doc){
		super("root");
		extractPageTree(doc.childNodes(), this);
	}
	
    private void extractPageTree(List<Node> childNodes, PageTreeNode pt) {
		for(Node n : childNodes){
			if (!excludedNode.contains(n.nodeName())){
				PageTreeNode tmp = new PageTreeNode(n.nodeName());
				extractPageTree(n.childNodes(), tmp);
				pt.addChild(tmp);
			}else{
				extractPageTree(n.childNodes(), pt);
			}
		}		
	}

	@Override
	public boolean equals(Object other) {
		if (!(other instanceof PageTreeNode)) {
			return false;
		}
		PageTreeNode to = (PageTreeNode) other;

		if (!data.equals(to.data)) {
			return false;
		}

		int numberOfChildren = getNumberOfChildren();
		if (numberOfChildren != to.getNumberOfChildren()) {
			return false;
		}
		
		for (int i = 0; i < numberOfChildren; i++) {
			if (!((PageTreeNode) getChildAt(i)).equals((PageTreeNode) to.getChildAt(i))) {
				return false;
			}
		}
		return true;
	}

	@Override
	public String toString() {
		return toString(0);
	}

	@Override
	public int hashCode() {
		return toString().hashCode();
	}
}
