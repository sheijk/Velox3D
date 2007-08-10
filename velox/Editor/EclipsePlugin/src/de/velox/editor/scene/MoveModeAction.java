package de.velox.editor.scene;

import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.commands.IHandler;
import org.eclipse.core.commands.IHandlerListener;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.ui.IEditorActionDelegate;
import org.eclipse.ui.IEditorPart;

import de.velox.VShowSelectionPart;
import de.velox.editor.views.SceneView;
import de.velox.editors.SceneEditor;

public class MoveModeAction implements IEditorActionDelegate, IHandler {
	private SceneEditor activeEditor = null;
	
	@Override
	public void setActiveEditor(IAction action, IEditorPart targetEditor) {
		if( targetEditor instanceof SceneEditor )
			activeEditor = (SceneEditor) targetEditor;
		else
			activeEditor = null;
	}

	private void exec() {
		SceneView.getDefaultInstance().SetSelectionMode( 
				VShowSelectionPart.EditMode.EMMove );
	}
	
	@Override
	public void run(IAction action) {
		exec();
	}

	@Override
	public void selectionChanged(IAction action, ISelection selection) {
	}

	@Override
	public void addHandlerListener(IHandlerListener handlerListener) {
	}

	@Override
	public void dispose() {
	}

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		exec();
		return null;
	}

	@Override
	public boolean isEnabled() {
		return true;
	}

	@Override
	public boolean isHandled() {
		return true;
	}

	@Override
	public void removeHandlerListener(IHandlerListener handlerListener) {
	}

}
