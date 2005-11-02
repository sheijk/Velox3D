package de.velox.editor.cgfx;

import org.eclipse.jface.text.DefaultTextDoubleClickStrategy;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.ITextDoubleClickStrategy;
import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.presentation.IPresentationReconciler;
import org.eclipse.jface.text.presentation.PresentationReconciler;
import org.eclipse.jface.text.rules.DefaultDamagerRepairer;
import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.source.ISourceViewer;
import org.eclipse.jface.text.source.SourceViewerConfiguration;

public class ViewConfig extends SourceViewerConfiguration {
	private DefaultTextDoubleClickStrategy doubleClickStrategy;
	private CGFXScanner scanner;
	private ColorManager colorManager;

	public ViewConfig(ColorManager colorManager) {
		this.colorManager = colorManager;
	}
	public String[] getConfiguredContentTypes(ISourceViewer sourceViewer) {
		return new String[] {
			IDocument.DEFAULT_CONTENT_TYPE,
			CGFXPartitionScanner.CGFX_COMMENT,
//			CGFXPartitionScanner.CGFX_TAG 
		};
	}
	public ITextDoubleClickStrategy getDoubleClickStrategy(
		ISourceViewer sourceViewer,
		String contentType) {
		if (doubleClickStrategy == null)
			doubleClickStrategy = new DefaultTextDoubleClickStrategy();
		return doubleClickStrategy;
	}

	protected CGFXScanner getCGFXScanner() {
		if (scanner == null) {
			scanner = new CGFXScanner(colorManager);
			scanner.setDefaultReturnToken(
				new Token(
					new TextAttribute(
						colorManager.getColor(ColorConstants.DEFAULT))));
		}
		return scanner;
	}
//	protected XMLTagScanner getXMLTagScanner() {
//		if (tagScanner == null) {
//			tagScanner = new XMLTagScanner(colorManager);
//			tagScanner.setDefaultReturnToken(
//				new Token(
//					new TextAttribute(
//						colorManager.getColor(ColorConstants.TAG))));
//		}
//		return tagScanner;
//	}

	public IPresentationReconciler getPresentationReconciler(ISourceViewer sourceViewer) {
		PresentationReconciler reconciler = new PresentationReconciler();

//		DefaultDamagerRepairer dr =
//			new DefaultDamagerRepairer(getXMLTagScanner());
//		reconciler.setDamager(dr, CGFXPartitionScanner.CGFX_TAG);
//		reconciler.setRepairer(dr, CGFXPartitionScanner.CGFX_TAG);

		// add syntax highlighting for source
		DefaultDamagerRepairer dr = new DefaultDamagerRepairer(getCGFXScanner());
		reconciler.setDamager(dr, IDocument.DEFAULT_CONTENT_TYPE);
		reconciler.setRepairer(dr, IDocument.DEFAULT_CONTENT_TYPE);

		// add syntax hightlighting for comments
		NonRuleBasedDamagerRepairer ndr =
			new NonRuleBasedDamagerRepairer(
				new TextAttribute(
					colorManager.getColor(ColorConstants.CGFX_COMMENT)));
		reconciler.setDamager(ndr, CGFXPartitionScanner.CGFX_COMMENT);
		reconciler.setRepairer(ndr, CGFXPartitionScanner.CGFX_COMMENT);

		return reconciler;
	}

}