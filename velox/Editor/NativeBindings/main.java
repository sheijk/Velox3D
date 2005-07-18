import de.velox.*;

public class main {
	static {
		System.loadLibrary("ScriptingDLL");
	}
	
	public static void main(String[] args) {
		v3d.Initialize();
		System.out.println("Hello from java");
		
		VPropertyManager propMngr = v3d.GetPropertyManager();
		String blup = v3d.ToString(propMngr.GetValue("blup"));
		
		VStringIter iter = propMngr.GetPropertyNames();
		while( iter.HasNext() ) {
			String name = iter.__ref__();
			System.out.println("Property has name: " + name);
			iter.Next();
		}
		
		System.out.println("property blup = " + blup);
		
		Foo foo = new Foo();
		foo.sayHello();
		v3d.Shutdown();
	}
}
