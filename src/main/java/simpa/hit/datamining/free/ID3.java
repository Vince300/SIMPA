package simpa.hit.datamining.free;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

 
public class ID3 {
	
	public static TreeNode Run(List<LinkedList<String>> columns_attributes,  LinkedList<String> col_class,
			Map<String, Nominal<String>> map_attributes, Map<Integer, String> array_attributes, int index_class) {
		/*System.out.println("----------------- Running ID3 ------------------------");
		System.out.println("\n--> array_attributes : ");
		System.out.println(array_attributes.toString());
		System.out.println("\n--> map_attributes : ");
		System.out.println(map_attributes.toString());
		System.out.println("\n--> columns attributes : ");
		System.out.println(columns_attributes.toString());
		System.out.println("\n--> col class : ");
		System.out.println(col_class.toString());
		System.out.println("\n--> index class : ");
		System.out.println(index_class);
		System.out.println("\n--> enum_class : ");
		System.out.println(map_attributes.get(array_attributes.get(index_class)).toString());*/

		float Global_Entropy = Entropy._Entropy(col_class, 
								map_attributes.get(array_attributes.get(index_class)));
		
		TreeNode NewNode = new TreeNode();
		
		if (columns_attributes.get(0).size() < 1) {
			Tag leaf = new Tag("Error", "Error");
			TreeNode.AddChildrenNode(NewNode, new TreeNode(leaf));
		}
		else if (columns_attributes.size() == 1)  {// attributNonCible vide
			Nominal<String> possible_values = map_attributes.get(array_attributes.get(0));
			String value = MostPresent(columns_attributes.get(0), possible_values.getLinkedList());
			String attribute = "class";
			Tag leaf = new Tag(attribute, value);
			TreeNode.AddChildrenNode(NewNode, new TreeNode(leaf));
		}
		else if (Global_Entropy == 0) {
			String value = col_class.get(0);
			String attribute = "class";
			Tag leaf = new Tag(attribute, value);
			TreeNode.AddChildrenNode(NewNode, new TreeNode(leaf));
		}
		else {

			int best_column = SelectBestColumn (col_class, columns_attributes, map_attributes, array_attributes, index_class, Global_Entropy);
			
			// Create array_attribute_next
			Map<Integer, String> array_attributes_next = new HashMap<Integer, String>(FilterArrAtt(array_attributes, best_column));
			
			// Create index_class_next
			int index_class_next = index_class;
			if (index_class > best_column)
				index_class_next--;
			
			// Create map_attribute_next
			Map<String, Nominal<String>> map_attributes_next = new HashMap<String, Nominal<String>>(map_attributes);
			map_attributes_next.remove(array_attributes.get(best_column));
			
			LinkedList<String> enum_value = new LinkedList<String>(map_attributes.get(array_attributes.get(best_column)).getLinkedList());
			Iterator<String> itr = enum_value.iterator();

			while (itr.hasNext()) {
				String current = new String(itr.next());
				
				// Create columns_attributes_next
				List<LinkedList<String>> columns_attributes_next = new ArrayList<LinkedList<String>>(FilterColAtt(columns_attributes, current, best_column));

				// Create col_class_next 
				LinkedList<String> col_class_next = new LinkedList<String>(columns_attributes_next.get(index_class_next));
			
				String attribute_name = array_attributes.get(best_column);
				Tag tag_child = new Tag(attribute_name, current);

				TreeNode Child = ID3.Run(columns_attributes_next, col_class_next, map_attributes_next, array_attributes_next, index_class_next);
				Child.setTag(tag_child);
				TreeNode.AddChildrenNode(NewNode, Child);
			}
		}
		return NewNode;
	}
	
	private static String MostPresent(LinkedList<String> column, LinkedList<String> possible_values) {
		String most_present = "";
		int nb_most_present = 0;
		Map<String, Integer> counter = new HashMap<String, Integer>();
		
		//init HashMap
		Iterator<String> itr = possible_values.iterator();
		while (itr.hasNext()) {
			counter.put(itr.next(), 0);
		}
		
		//count 
		Iterator<String> it = column.iterator();
		while(it.hasNext()) {
			String current = it.next();
			int current_counter = counter.get(current);
			counter.remove(current);
			counter.put(current, current_counter+1);
		}
		
		//Select best
		Iterator<Map.Entry<String, Integer>> it2 = counter.entrySet().iterator();
		while (it2.hasNext()) {
			Map.Entry<String, Integer> pairs =it2.next();
			if (pairs.getValue() > nb_most_present) {
				nb_most_present = pairs.getValue();
				most_present = pairs.getKey();
			}
		}
		return most_present;
	}
	
	private static int SelectBestColumn (LinkedList<String> column_class, List<LinkedList<String>> columns_attributes, Map<String, 
			Nominal<String>> map_attributes, Map<Integer, String> array_attributes, int index_class, float Global_Entropy) {
		int best_column = 0;
		float best_gain = 0;
		float gain = 0;
		for (int i = 0; i < columns_attributes.size(); i++) {
			if (i != index_class) {
				if (map_attributes.get(array_attributes.get(i)) != null)
					Entropy.gain(column_class, columns_attributes.get(i), map_attributes.get(array_attributes.get(index_class)), map_attributes.get(array_attributes.get(i)), Global_Entropy);
				
				if (gain > best_gain) {
					best_gain = gain;
					best_column = i;
				}
			}
		}
		return best_column;
	}
	
	private static List<LinkedList<String>> DeleteColumn (List<LinkedList<String>> columns_attributes, int index) {
		int size = columns_attributes.size();
		List<LinkedList<String>> col_att = new ArrayList<LinkedList<String>>();
		for (int i = 0; i < size; i++) {
			if (i != index) {
	            col_att.add(new LinkedList<String>(columns_attributes.get(i)));
			}
		}
		return col_att;
	}
	
	private static List<LinkedList<String>> FilterColAtt(List<LinkedList<String>> columns_attributes, String value, int index) {
		List<Iterator<String>> LL_it = new ArrayList<Iterator<String>>();
		String [] LL_values = new String[columns_attributes.size()];
		List<LinkedList<String>> filter = new ArrayList<LinkedList<String>>();
		
		for (int i = 0; i < columns_attributes.size(); i++) {
			LL_it.add(columns_attributes.get(i).iterator());
			LL_values[i] = "";
			filter.add(new LinkedList<String>());
		}
		
		while (LL_it.get(index).hasNext()) {
			for(int i = 0; i < LL_it.size(); i++) {
				if (LL_it.get(i).hasNext())
					LL_values[i] = LL_it.get(i).next();
			}
			
			if (LL_values[index].equals(value)) {
				for(int i = 0; i < filter.size(); i++){
					filter.get(i).add(LL_values[i]);
				}
			}
		}
		
		return DeleteColumn(filter, index);
	}
	
	private static Map<Integer, String> FilterArrAtt(Map<Integer, String> array_attributes, int best_column) {
		Map<Integer, String> arr_att = new HashMap<Integer, String>();
		
		Iterator<Map.Entry<Integer, String>> it = array_attributes.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry<Integer, String> pairs = it.next(); 
			if (pairs.getKey() < best_column) {
				arr_att.put(pairs.getKey(), pairs.getValue());
			}
			else if (pairs.getKey() > best_column)
				arr_att.put(pairs.getKey()-1, pairs.getValue());
		}
		return arr_att;
	}
}
